#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rtthread.h>
#include <channel.h>

// #include "lwip/netifapi.h"

// #include "netif/etharp.h"

#include "lwip/pbuf.h"

#include <unet.h>
// #include <lwip/sockets.h>   /* socklen_t */
// #include <lwip/netdb.h>     /* lwip_gethostbyname */

// #include <lwip/api.h>

#include "drv_eth.h"

#include "netdev.h"
#include "usocket.h"

#define NIOCTL_GADDR        0x01

/* private commands */
#define UNET_NETDEV_REQ_ATTACH      101
#define UNET_NETDEV_REQ_DETACH      102

#ifndef ETHERNET_MTU
#define ETHERNET_MTU        1500
#endif

#define MAX_ETHERNET_FRAME 1518

extern int lwip_system_init(void);

int  unet_channel = -1;  /* created in kernel */
static int stack_channel = -1;  /* implement system calls */
// static int  data_channel = -1;  /* only handle UNET_PACKET_IND */

const char *chn_name = "lwIPKit";
const char *data_name = "dataInd";

/*
 * lwIPKit could be initialized at most once. If the stack channel exists, we
 * assume lwIPKit has been set up and no further actions should be taken. Three
 * cases are distinguished by the return value:
 * -1: failures happened during initialization, we could do nothing;
 *  0: initialization completes successfully, further actions can be carried on
 *  1: initialization has been done before, we could do anything but another
 *  initialization
 */
int stack_init(void)
{
    /* stack channel as a flag whether the stack has been initialized */
    stack_channel = rt_channel_open(chn_name, O_CREAT);
    if (stack_channel < 0) return 1;    /* initialization has been done */

    // /* If data_channel already exists, something must be wrong, fix it */
    // data_channel  = rt_channel_open(data_name, O_CREAT | O_EXCL);
    // if (data_channel < 0) goto close_stack_channel;

    // /* During execution, stack_channel and data_channel are created and opened
    //  * only once when initialized. However, unet_channel might be opened many
    //  * times: first opened when initialized, then opened and closed each time we
    //  * attach or detach a network device. */
    // unet_channel = rt_channel_open("unet", O_RDWR);
    // if (unet_channel < 0) goto close_data_channel;

    // /* attach ip stack in unet
    //  * UNET_TCPIP_STACK_ATTACH with
    //  * channel name offset
    //  * data channel name offset
    //  * -- data --
    //  * stack_channel_name
    //  * stack_data_channel_name
    //  */
    // int shmid = channel_compose_cmd2(UNET_TCPIP_STACK_ATTACH, NULL, NULL, strlen(chn_name) + 1 +
    //     strlen(data_name) + 1);
    // struct channel_cmd *cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
    // if (cmd)
    // {
    //     cmd->argv[0] = (void *)(size_t)(CHANNEL_CMD_OFFSET);
    //     cmd->argv[1] = (void *)(size_t)(CHANNEL_CMD_OFFSET  + strlen(chn_name) + 1);

    //     uint8_t *ptr = (uint8_t*)cmd + CHANNEL_CMD_OFFSET;
    //     strcpy((char*)ptr, chn_name);
    //     ptr = (uint8_t*)cmd + (CHANNEL_CMD_OFFSET  + strlen(chn_name) + 1);
    //     strcpy((char*)ptr, data_name);

    //     lwp_shmdt(cmd);
    // }

    // int ret = (int)(size_t)channel_cmd_send_recv(unet_channel, (void *)(size_t)shmid);
    // lwp_shmrm(shmid);

    // if (ret < 0)
    // {
    //     printf("attach stack failed!\n");
    //     goto close_unet_channel;
    // }

    /* start the TCPIP thread */
    lwip_system_init();
    return 0;

// close_unet_channel:
//     rt_channel_close(unet_channel);
//     data_channel = -1;
// close_data_channel:
//     rt_channel_close(data_channel);
//     data_channel = -1;
// close_stack_channel:
//     rt_channel_close(stack_channel);
//     stack_channel = -1;
//     return -1;      /* initialization fails */
}

// static void stack_data_input(void* parameter)
// {
//     struct channel_cmd *cmd;
//     // const char *name;

//     while (1)
//     {
//         int shmid = (int)(size_t)channel_cmd_recv(data_channel);
//         if (shmid >= 0)
//         {
//             cmd = lwp_shmat(shmid, NULL);
//             switch (cmd->cmd)
//             {
//             case UNET_SRV_DATA_INPUT:
//             {
//                 struct netif *netif = (struct netif*)cmd->argv[1];
//                 int length = (int)(size_t)cmd->argv[2];
//                 uint8_t *buffer = (uint8_t*)(cmd + 1);

//                 if (netif == NULL)
//                 {
//                     printf("NULL netif\n");
//                     break;
//                 }
                
//                 struct pbuf *p = pbuf_alloc(PBUF_RAW, MAX_ETHERNET_FRAME, PBUF_POOL);
//                 if (p)
//                 {
//                     /* copy buffer */
//                     pbuf_take(p, buffer, length);
//                     /* notify to stack */
//                     if (netif->input(p, netif) != ERR_OK)
//                     {
//                         printf("netif->input failed\n");
//                         pbuf_free(p);
//                         p = NULL;
//                     }
//                     lwp_shmdt(cmd);
//                     channel_cmd_reply(data_channel, (void *)(size_t)0);
//                 }
//                 else
//                 {
//                     printf("%s pbuf alloc failed\n",__func__);
//                     lwp_shmdt(cmd);
//                     channel_cmd_reply(data_channel, (void *)(size_t)-1);
//                 }
//                 break;
//             }
//             default:
//                 break;
//             }
//         }
//     }
// }

#define POLLIN     0x1
#define POLLOUT    0x2
#define POLLERR    0x4

#ifndef SELWAIT_T
#define SELWAIT_T u8_t
#endif

//static int poll_send_count = 0;
static int lwip_send_count = 0;
/** Contains all internal pointers and states used for a socket */
struct lwip_sock {
  /** sockets currently are built on netconns, each socket has one netconn */
  struct netconn *conn;
  /** data that was left from the previous read */
  void *lastdata;
  /** offset in the data that was left from the previous read */
  u16_t lastoffset;
  /** number of times data was received, set by event_callback(),
      tested by the receive and select functions */
  s16_t rcvevent;
  /** number of times data was ACKed (free send buffer), set by event_callback(),
      tested by select */
  u16_t sendevent;
  /** error happened for this socket, set by event_callback(), tested by select */
  u16_t errevent;
  /** last error that occurred on this socket (in fact, all our errnos fit into an u8_t) */
  u8_t err;
  /** counter of how many threads are waiting for this socket using select */
  SELWAIT_T select_waiting;

};
extern struct lwip_sock *lwip_tryget_socket(int s);
extern struct lwip_sock * get_socket(int s);
extern int access_is_blocking(u32_t flags, struct lwip_sock *sock);
int stack_run(void)
{
    /* local variables */
    int socket, len, result;
    struct sockaddr *psockaddr;
    socklen_t socklen;
    // socklen_t *psocklen;
    // struct hostent *phostent;

    int domain, type, protocol;

    u32_t flags;

    void *data;
    size_t size;

    socklen_t tolen, *fromlen;
    // char *pname;

    // const char *nodename;
    // const char *servname;
    // const struct addrinfo *hints;
    // struct addrinfo *u_ai;

    struct channel_cmd *cmd;
    // struct lwip_sock *sock = RT_NULL;

    /* run stack event loop */
    while (1)
    {
        int shmid = (int)(size_t)channel_cmd_recv(stack_channel);
        if (shmid >= 0)
        {
            cmd = lwp_shmat(shmid, NULL);
            if (!cmd)
            {
                lwp_shmrm(shmid);
                continue;
            }

            switch (cmd->cmd)
            {
            /* handle socket requests */
            case UNET_SRV_CMD_SOCKET:
                domain = (int)(size_t)cmd->argv[0];
                type = (int)(size_t)cmd->argv[1];
                protocol = (int)(size_t)cmd->argv[2];
                socket = socket_internal(domain, type, protocol);
                lwp_shmdt(cmd);
                channel_cmd_reply(stack_channel, (void *)(size_t)socket);
                break;

            // case UNET_SRV_CMD_CLOSE:
            //     socket = (int)(size_t)cmd->argv[0];

            //     cmd->argv[0] = get_socket(socket);

            //     result = lwip_close(socket);

            //     lwp_shmdt(cmd);
            //     channel_cmd_reply(stack_channel, (void *)(size_t)result);
            //     break;

            case UNET_SRV_CMD_BIND:
                socket = (int)(size_t)cmd->argv[0];
                psockaddr = (void *)(size_t)cmd + UNET_CMD_OFFSET;
                len = (int)(size_t)cmd->argv[1];

                result = bind_internal(socket, psockaddr, len);

                lwp_shmdt(cmd);
                channel_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_LISTEN:
                socket = (int)(size_t)cmd->argv[0];

                result = listen_internal(socket, (int)(size_t)cmd->argv[1]);

                lwp_shmdt(cmd);
                channel_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_CONNECT:
                socket = (int)(size_t)cmd->argv[0];
                psockaddr = (void *)(size_t)cmd + UNET_CMD_OFFSET;
                len = (int)(size_t)cmd->argv[1];

                result = connect_internal(socket, psockaddr, len);

                lwp_shmdt(cmd);
                channel_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_ACCEPT:
                socket = (int)(size_t)cmd->argv[0];
                psockaddr = (void *)(size_t)cmd + UNET_CMD_OFFSET;
                result = accept_internal(socket, psockaddr, (socklen_t *)&cmd->argv[1]);
                lwp_shmdt(cmd);
                channel_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_SENDTO:
                socket = (int)(size_t)cmd->argv[0];
                size = (size_t)cmd->argv[1];
                flags = (int)(size_t)cmd->argv[2];
                tolen = (int)(size_t)cmd->argv[3];
                data = (void *)(size_t)cmd + UNET_CMD_OFFSET;

                lwip_send_count++;
                if(tolen  == 0)
                {
                    result = send_internal(socket, data, size, flags);
                }
                else
                {
                    psockaddr = (void *)(size_t)cmd + UNET_CMD_OFFSET + size;
                    result = sendto_internal(socket, data, size, flags, psockaddr, tolen);
                }
                if(result <= 0)
                {
                    rt_kprintf("%s line %d sendto error\n",__func__,__LINE__);
                }
                lwp_shmdt(cmd);
                channel_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_RECVFROM:
                socket = (int)(size_t)cmd->argv[0];
                size = (size_t)cmd->argv[1];
                flags = (int)(size_t)cmd->argv[2];
                fromlen = (socklen_t*)cmd->argv[3];
                data = (void *)(size_t)cmd + UNET_CMD_OFFSET;

                if(fromlen == RT_NULL)
                {
                    result = recv_internal(socket, data, size, flags);
                }
                else
                {
                    psockaddr =  (void *)(size_t)cmd + UNET_CMD_OFFSET + size;
                    result = recvfrom_internal(socket, data, size, flags , psockaddr, fromlen);
                }

                lwp_shmdt(cmd);
                channel_cmd_reply(stack_channel, (void *)(size_t)result);
                break;


            // case UNET_SRV_CMD_GETSOCKOPT:
            //     socket = (int)(size_t)cmd->argv[0];
            //     int level = (int)(size_t)cmd->argv[1];
            //     int opt = (int)(size_t)cmd->argv[2];
            //     void *optval = (void *)(size_t)cmd + (size_t)cmd->argv[3];
            //     psocklen = (socklen_t *)&cmd->argv[4];

            //     result = lwip_getsockopt(socket, level, opt, optval, psocklen);
            //     RT_ASSERT(*psocklen < UNET_RECV_DATA_MAXLEN);

            //     lwp_shmdt(cmd);
            //     channel_cmd_reply(stack_channel, (void *)(size_t)result);
            //     break;

            case UNET_SRV_CMD_SETSOCKOPT:
            {
                socket = (int)(size_t)cmd->argv[0];
                int level = (int)(size_t)cmd->argv[1];
                int opt = (int)(size_t)cmd->argv[2];
                socklen = (socklen_t)(size_t)cmd->argv[3];
                void *optval =  (void *)(size_t)cmd + UNET_CMD_OFFSET;

                result = setsockopt_internal(socket, level, opt, optval, socklen);

                lwp_shmdt(cmd);
                channel_cmd_reply(stack_channel, (void *)(size_t)result);
                break;
            }

            // case UNET_SRV_CMD_SHUTDOWN:
            //     socket = (int)(size_t)cmd->argv[0];

            //     result = lwip_shutdown(socket, (int)(size_t)cmd->argv[1]);

            //     lwp_shmdt(cmd);
            //     channel_cmd_reply(stack_channel, (void *)(size_t)result);
            //     break;

            // case UNET_SRV_CMD_GETPEERNAME:
            //     socket = (int)(size_t)cmd->argv[0];
            //     psockaddr = (void *)(size_t)cmd + (size_t)cmd->argv[1];
            //     psocklen = (socklen_t *)&cmd->argv[2];

            //     result = lwip_getpeername(socket, psockaddr, psocklen);
            //     RT_ASSERT(*psocklen < UNET_RECV_DATA_MAXLEN);

            //     lwp_shmdt(cmd);
            //     channel_cmd_reply(stack_channel, (void *)(size_t)result);
            //     break;

            // case UNET_SRV_CMD_GETSOCKNAME:
            //     socket = (int)(size_t)cmd->argv[0];
            //     psockaddr = (void *)(size_t)cmd + (size_t)cmd->argv[1];
            //     psocklen = (socklen_t *)&cmd->argv[2];

            //     result = lwip_getsockname(socket, psockaddr, psocklen);
            //     RT_ASSERT(*psocklen < UNET_RECV_DATA_MAXLEN);

            //     lwp_shmdt(cmd);
            //     channel_cmd_reply(stack_channel, (void *)(size_t)result);
            //     break;

            // case UNET_SRV_CMD_FCNTL:
            //     socket = (int)(size_t)cmd->argv[0];
            //     result = lwip_fcntl(socket, (int)(size_t)cmd->argv[1], (int)(size_t)cmd->argv[2]);

            //     lwp_shmdt(cmd);
            //     channel_cmd_reply(stack_channel, (void *)(size_t)result);
            //     break;

    //         case UNET_SRV_CMD_IOCTL:
    //             socket = (int)(size_t)cmd->argv[0];
    //             result = lwip_ioctl(socket, (int)(size_t)cmd->argv[1], (int *)&cmd->argv[2]);

    //             lwp_shmdt(cmd);
    //             channel_cmd_reply(stack_channel, (void *)(size_t)result);
    //             break;

    //         case UNET_SRV_CMD_GETHOSTBYNAME:
    //             pname = (void *)(size_t)cmd + UNET_CMD_OFFSET;
    //             phostent = lwip_gethostbyname(pname);
    //             if (phostent)
    //                 *((ip_addr_t *) &cmd->argv[0]) = *((ip_addr_t *) phostent->h_addr);

    //             lwp_shmdt(cmd);
    //             channel_cmd_reply(stack_channel, phostent);
    //             break;

    //         case UNET_SRV_CMD_GETADDRINFO:
    //             nodename = (const char *)cmd + (size_t)cmd->argv[0];
    //             servname = (const char *)cmd + (size_t)cmd->argv[1];

    //             if(servname[0] == 0)
    //             {
    //                 servname = NULL;
    //             }
    //             hints = (const struct addrinfo *)((void *)(size_t)cmd + (size_t)cmd->argv[2]);

    //             /* store the pointer to the structure 'addrinfo' in user mode
    //              * into the 4th argument */
    //             result = lwip_getaddrinfo(nodename, servname, hints, &u_ai);

    //             if (result == 0)
    //             {
    //                 rt_memcpy((void *)(size_t)cmd + (size_t)cmd->argv[3], u_ai, sizeof(*u_ai));
    //                 cmd->argv[3] = u_ai;

    //                 rt_memcpy((void *)(size_t)cmd + (size_t)cmd->argv[4], u_ai->ai_addr, sizeof(struct sockaddr));
    //             }
    //             else
    //             {
    //                 result = -1;
    //             }
    //             lwp_shmdt(cmd);
    //             channel_cmd_reply(stack_channel, (void *)(size_t)result);
    //             break;

    //         case UNET_SRV_CMD_FREEADDRINFO:
    //             u_ai = cmd->argv[0];
    //             lwip_freeaddrinfo(u_ai);

    //             lwp_shmdt(cmd);
    //             channel_cmd_reply(stack_channel, u_ai);
    //             break;

    //         case UNET_SRV_CMD_POLL:
    //             /* arguments: maxfd, *readset, *writeset, *exceptset, *timeout */
    //             socket = (int)(size_t)cmd->argv[0];
    //             int mask = 0;
    //             sock = lwip_tryget_socket(socket);
    //             if (sock != NULL)
    //             {
    // #if LWIP_VERSION >= 0x20100ff
    //                 if ((void*)(sock->lastdata.pbuf) || sock->rcvevent)
    // #else
    //                 if ((void *)(sock->lastdata) || sock->rcvevent)
    // #endif
    //                 {
    //                     mask |= POLLIN;
    //                 }
    //                 if (sock->sendevent)
    //                 {
    //                     mask |= POLLOUT;
    //                 }
    //                 if (sock->errevent)
    //                 {
    //                     mask |= POLLERR;
    //                     /* clean error event */
    //                     sock->errevent = 0;
    //                 }
    //             }
    //             /* Note, the actual socket is 'maxfd - 1'. */
    //             cmd->argv[0] = get_socket(socket);
    //             lwp_shmdt(cmd);
    //             channel_cmd_reply(stack_channel, (void *)(size_t)mask);
    //             break;

            default :
                break;
            }
        }
    }

    return 0;
}

static void lwipkit_status(void)
{
}

/* lwIPKit initialization should be done once at most */
static void lwipkit_usage(void)
{
    printf("lwIPKit Usage:\n"
            "\tlwIPKit               :  run lwIPKit, wait for ethdev to attach\n"
            "\tlwIPKit attach   <eth>:  attach the device <eth> to lwIPKit\n"
            "\tlwIPKit deattach <eth>:  de-attach the device <eth> from lwIPKit\n"
            "\tlwIPKit default  <eth>:  set <eth> as the default device\n"
            "\tlwIPKit status        :  show the status of running lwIPKIt\n");
}

/* entry point */
extern void sal_init(void);
extern int dfs_init(void);
int main(int argc, char **argv)
{
    int initialized = 0;

    int data_channel = -1;  /* local variable, not the global one */
    int shmid = -1;
    struct channel_cmd *cmd = NULL;

    /* no arguments, we want to run lwIPKit as a server */
    if (argc < 2)
    {        
        printf("lwIPKit: starts to run as the server");
        initialized = stack_init();
        if (initialized < 0)
        {
            printf(" ...failed!\n");
            return -1;
        }
        else if (initialized > 0)   /* valid lwIPKit process exists */
        {
            printf(" ...skipped! Already initialized\n");
            return 0;
        }
        else
        {
            // netdev_list_init();
            printf(" ...succeeded!\n");

            // rt_thread_t tid = rt_thread_create("ipdata", stack_data_input, NULL, 8192,
            //     25, 10);            /* handle the input data */
            // if (tid) rt_thread_startup(tid);

            printf("lwIPKit: init eth dev...");
            const char * eth_name;
            initialized = imx6ul_eth_init(0, &eth_name);
            if (initialized < 0)
            {
                printf(" ...failed!\n");
                return -1;
            }
            else if (initialized > 0)   /* valid lwIPKit process exists */
            {
                printf(" ...skipped! Already initialized\n");
                return 0;
            } 
            else 
            {
                printf("succeeded\n");
                dfs_init();
                sal_init();
                // netdev_init(eth_name);
            }

            stack_run();            /* handle network requests, never return */
        }
    }

    /* attach the device */
    if (argc >= 3 && strncmp(argv[1], "attach", 6) == 0)
    {
        int static_ip = 0;
        printf("lwIPKit: attach device %s\n", argv[2]);

        data_channel = rt_channel_open(data_name, O_RDWR);
        if (data_channel < 0)
        {
            printf("cannot open data_channel, please make sure lwIPKit server is running!\n");
            return -1;
        }

        shmid = channel_compose_cmd1(UNET_NETDEV_REQ_ATTACH, (void *)(size_t)static_ip, strlen(argv[2]) + 1);
        cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
        if (cmd)
        {
            strcpy(CHANNEL_CMD_DATA(cmd), argv[2]);
            lwp_shmdt(cmd);
        }
        channel_cmd_send(data_channel, (void *)(size_t)shmid);
        rt_channel_close(data_channel);

        return 0;
    }

    /* deattach the device and restore it to the uninitialized state */
    if (argc == 3)
    {
        if (strncmp(argv[1], "deattach", 8) == 0)
        {
            printf("lwIPKit: de-attach device %s\n", argv[2]);

            data_channel = rt_channel_open(data_name, O_RDWR);
            if (data_channel < 0)
            {
                printf("cannot open data_channel, please make sure lwIPKit server is running!\n");
                return -1;
            }

            shmid = channel_compose_cmd0(UNET_NETDEV_REQ_DETACH, strlen(argv[2]) + 1);
            cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
            if (cmd)
            {
                strcpy(CHANNEL_CMD_DATA(cmd), argv[2]);
                lwp_shmdt(cmd);
            }
            channel_cmd_send(data_channel, (void *)(size_t)shmid);
            rt_channel_close(data_channel);

            return 0;
        }


        if (strncmp(argv[1], "default", 8) == 0)
        {
            printf("lwIPKit: set the default device %s", argv[2]);
            //eth_set_default(argv[2]);
            return 0;
        }
    }

    /* show the status */
    if (argc == 2 && strncmp(argv[1], "status", 6) == 0)
    {
        printf("lwIPKit: the status of the attached devices as follows\n");
        lwipkit_status();
        return 0;
    }

    lwipkit_usage();
    return -1;
}

