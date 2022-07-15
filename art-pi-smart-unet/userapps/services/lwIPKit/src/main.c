#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rtthread.h>
#include <channel.h>

#include "lwip/netifapi.h"

#include "netif/etharp.h"

#include "lwip/inet.h"
#include "lwip/pbuf.h"

#include "srv_ping.h"

#include <unet.h>
#include <lwip/sockets.h>   /* socklen_t */
#include <lwip/netdb.h>     /* lwip_gethostbyname */

#include <lwip/api.h>

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
static int  data_channel = -1;  /* only handle UNET_PACKET_IND */

const char *chn_name = "lwIPKit";
const char *data_name = "dataInd";

static uint8_t tx_buffer[2048];

/* All the netdev managed by lwIPKit are attached in 'netdev_list', which is
 * protected by 'netdev_list_lock'. */
#define NETDEV_ITEM_MAX     4
static struct
{
    void *netdev_id;
    char name[2];
} netdev_list[NETDEV_ITEM_MAX];
static rt_sem_t netdev_list_lock;

static int netdev_list_init(void)
{
    memset(netdev_list, 0x0, sizeof(netdev_list));
    netdev_list_lock = rt_sem_create("netdev_list_lock", 1, RT_IPC_FLAG_FIFO);
    return 0;
}

static int netdev_list_add(void* netdev_id, const char *name)
{
    int index;

    rt_sem_take(netdev_list_lock, RT_WAITING_FOREVER);
    /* make sure the device has not been attached before */
    for (index = 0; index < NETDEV_ITEM_MAX; index ++)
    {
        if (strcmp(netdev_list[index].name, name) == 0 &&
                netdev_list[index].netdev_id == netdev_id)
        {
            rt_sem_release(netdev_list_lock);
            return -1;
        }
    }

    for (index = 0; index < NETDEV_ITEM_MAX; index ++)
    {
        if (netdev_list[index].netdev_id == NULL)
        {
            netdev_list[index].netdev_id = netdev_id;
            strncpy(netdev_list[index].name, name, 2);

            rt_sem_release(netdev_list_lock);
            return 0;
        }
    }

    rt_sem_release(netdev_list_lock);
    return -1;
}

static int netdev_list_remove(void* netdev_id, const char *name)
{
    int index;

    rt_sem_take(netdev_list_lock, RT_WAITING_FOREVER);
    for (index = 0; index < NETDEV_ITEM_MAX; index ++)
    {
        if (strcmp(netdev_list[index].name, name) == 0 &&
                netdev_list[index].netdev_id == netdev_id)
        {
            netdev_list[index].netdev_id = NULL;
            rt_sem_release(netdev_list_lock);
            return 0;
        }
    }

    rt_sem_release(netdev_list_lock);
    return -1;
}

void *netdev_get_by_name(const char *name)
{
    int index;

    rt_sem_take(netdev_list_lock, RT_WAITING_FOREVER);
    for (index = 0; index < NETDEV_ITEM_MAX; index ++)
    {
        if (strncmp(netdev_list[index].name, name, 2) == 0)
        {
            rt_sem_release(netdev_list_lock);
            return netdev_list[index].netdev_id;
        }
    }

    rt_sem_release(netdev_list_lock);
    return NULL;
}

err_t ethernetif_linkoutput(struct netif *netif, struct pbuf *p)
{
    struct rt_device* devid;

    devid = (struct rt_device*)netif->state;

    pbuf_copy_partial(p, tx_buffer, p->tot_len, 0);
    rt_device_write(devid, -1, tx_buffer, p->tot_len);

    return ERR_OK;
}

/* Attach the device to lwIPKit. This function is invoked in a separate process
 * and lwIPKit server must have been running. To complete the task, unet_channel
 * must be opened and closed temporarily. */
static err_t eth_netif_device_init(struct netif *netif)
{
    struct rt_device *devid;

    devid = (struct rt_device*)netif->state;
    if (devid != RT_NULL)
    {
        netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

#if LWIP_IGMP
        /* IGMP support */
        netif->flags |= NETIF_FLAG_IGMP;
#endif

#if LWIP_IPV6
        netif->output_ip6 = ethip6_output;
        netif->ip6_autoconfig_enabled = 1;
        netif_create_ip6_linklocal_address(netif, 1);

#if LWIP_IPV6_MLD
        netif->flags |= NETIF_FLAG_MLD6;

        /*
        * For hardware/netifs that implement MAC filtering.
        * All-nodes link-local is handled by default, so we must let the hardware know
        * to allow multicast packets in.
        * Should set mld_mac_filter previously. */
        if (netif->mld_mac_filter != NULL)
        {
            ip6_addr_t ip6_allnodes_ll;
            ip6_addr_set_allnodes_linklocal(&ip6_allnodes_ll);
            netif->mld_mac_filter(netif, &ip6_allnodes_ll, NETIF_ADD_MAC_FILTER);
        }
#endif /* LWIP_IPV6_MLD */

#endif /* LWIP_IPV6 */

        /* set default netif */
        if (netif_default == RT_NULL)
            netif_set_default(netif);

#if LWIP_DHCP
        /* set interface up */
        netif_set_up(netif);
        /* if this interface uses DHCP, start the DHCP client */
        dhcp_start(netif);
#else
        /* set interface up */
        netif_set_up(netif);
#endif

        //netif_set_addr(netif, ipaddr, netmask, gw);
        /* set link_up for this netif */
        netif_set_link_up(netif);

        /* open device */
        if (rt_device_open(devid, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
        {
            return ERR_IF;
        }

        return ERR_OK;
    }

    return ERR_IF;
}

static int eth_device_init_netif(const char *name, struct netif *netif)
{
    struct rt_device *devid = NULL;

    devid = rt_device_find(name);
    if (devid)
    {
        ip4_addr_t ipaddr, netmask, gw;

#if LWIP_DHCP
        /* add this netif to the system */
        IP4_ADDR(&ipaddr, 0, 0, 0, 0);
        IP4_ADDR(&gw, 0, 0, 0, 0);
        IP4_ADDR(&netmask, 0, 0, 0, 0);
#else
        ipaddr.addr = inet_addr(RT_LWIP_IPADDR);
        gw.addr = inet_addr(RT_LWIP_GWADDR);
        netmask.addr = inet_addr(RT_LWIP_MSKADDR);
#endif

        netifapi_netif_add(netif, &ipaddr, &netmask, &gw, devid, eth_netif_device_init, tcpip_input);

        /* get hardware MAC address */
        rt_device_control(devid, NIOCTL_GADDR, netif->hwaddr);
    }

    return 0;
}

struct netif* eth_netif_create(const char* name)
{
    struct netif *netif = NULL;

    netif = (struct netif*) calloc (1, sizeof(struct netif));
    if (netif)
    {
        /* set name */
        netif->name[0] = name[0];
        netif->name[1] = name[1];

        /* set hw address to 6 */
        netif->hwaddr_len   = 6;
        /* maximum transfer unit */
        netif->mtu          = ETHERNET_MTU;

        /* set output */
        netif->output       = etharp_output;
        netif->linkoutput   = ethernetif_linkoutput;

#if LWIP_NETIF_HOSTNAME
        /* Initialize interface hostname */
        netif->hostname = "rtthread";
#endif /* LWIP_NETIF_HOSTNAME */
    }

    return netif;
}

int eth_attach(const char* name)
{
    struct netif* netif = NULL;
    void *netdev = NULL;

    /* if the net device has been attached */
    netdev = netdev_get_by_name(name);
    if (netdev)
    {
        printf("netdev %s has been attached!\n", name);
        return -1;
    }

    /* create netif firstly */
    netif = eth_netif_create(name);
    if (netif)
    {
        /* attach device and netif to a netdev in the kernel */
        int shmid = channel_compose_cmd1(UNET_NETDEV_NETIF_ATTACH, netif, strlen(name) + 1);
        struct channel_cmd *cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
        if (cmd)
        {
            strcpy(CHANNEL_CMD_DATA(cmd), name);
            lwp_shmdt(cmd);
        }

        netdev = channel_cmd_send_recv(unet_channel, (void *)(size_t)shmid);
        lwp_shmrm(shmid);

        if (netdev)
        {
            /* set netdev with name */
            netdev_list_add(netdev, name);

            /* add netif into lwIP */
            eth_device_init_netif(name, netif);
        }
        else
        {
            free(netif);
            return -1;
        }
    }
    else
    {
        printf("failed to allocate netif for the device %s!\n", name);
        return -1;
    }

    return 0;
}

static int eth_deattach(const char* name)
{
    struct netif* netif = NULL;
    void *netdev = NULL;

    /* if the net device was not attached */
    netdev = netdev_get_by_name(name);
    if (!netdev)
    {
        printf("netdev %s was not attached!\n", name);
        return 0;
    }

        int shmid = channel_compose_cmd1(UNET_NETDEV_NETIF_DETACH, netdev, strlen(name) + 1);
        struct channel_cmd *cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
        if (cmd)
        {
            strcpy(CHANNEL_CMD_DATA(cmd), name);
            lwp_shmdt(cmd);
        }

        netif = channel_cmd_send_recv(unet_channel, (void *)(size_t)shmid);
        lwp_shmrm(shmid);

        if (netif)
        {
            /* remove netdev with name */
            netdev_list_remove(netdev, name);

            struct rt_device *devid;
            devid = netif->state;
            rt_device_close(devid);

            /* remove netif from lwIP */
            netifapi_netif_remove(netif);
            free(netif);
        }
        else
        {
            printf("netdev %s was registered without netif!\n", name);
            return -1;
        }

    return 0;
}

/* interfaces provided by 'netdev' to LWIP in user mode */
/* Auxiliary function added by microkernel RT-Thread.
 *
 * The pointer to the 'netdev' could not be found by name directly, which is
 * done by kernel. */

void netdev_low_level_set_ipaddr(void *netdev, const ip_addr_t *ip_addr)
{
    int shmid;
    struct channel_cmd *cmd;

    shmid = channel_compose_cmd2(UNET_NETDEV_SETIPADDR, netdev, NULL, sizeof(ip_addr_t));
    if (shmid < 0)
        return;

    cmd = lwp_shmat(shmid, NULL);
    if (ip_addr)
    {
        cmd->argv[1] = (void *)(size_t)CHANNEL_CMD_OFFSET;
        rt_memcpy((void *)(size_t)cmd + CHANNEL_CMD_OFFSET, ip_addr, sizeof(ip_addr_t));
    }
    lwp_shmdt(cmd);

    channel_cmd_send_recv(unet_channel, (void *)(size_t)shmid);
    lwp_shmrm(shmid);
}

void netdev_low_level_set_netmask(void *netdev, const ip_addr_t *netmask)
{
    int shmid;
    struct channel_cmd *cmd;

    shmid = channel_compose_cmd2(UNET_NETDEV_SETNETMASK, netdev, NULL, sizeof(ip_addr_t));
    if (shmid < 0)
        return;

    cmd = lwp_shmat(shmid, NULL);
    if (netmask)
    {
        cmd->argv[1] = (void *)(size_t)CHANNEL_CMD_OFFSET;
        rt_memcpy((void *)(size_t)cmd + CHANNEL_CMD_OFFSET, netmask, sizeof(ip_addr_t));
    }
    lwp_shmdt(cmd);

    channel_cmd_send_recv(unet_channel, (void *)(size_t)shmid);
    lwp_shmrm(shmid);
}

void netdev_low_level_set_gw(void *netdev, const ip_addr_t *gw)
{
    int shmid;
    struct channel_cmd *cmd;

    shmid = channel_compose_cmd2(UNET_NETDEV_SETGW, netdev, NULL, sizeof(ip_addr_t));
    if (shmid < 0)
        return;

    cmd = lwp_shmat(shmid, NULL);
    if (gw)
    {
        cmd->argv[1] = (void *)(size_t)CHANNEL_CMD_OFFSET;
        rt_memcpy((void *)(size_t)cmd + CHANNEL_CMD_OFFSET, gw, sizeof(ip_addr_t));
    }
    lwp_shmdt(cmd);

    channel_cmd_send_recv(unet_channel, (void *)(size_t)shmid);
    lwp_shmrm(shmid);
}

void netdev_low_level_set_status(void *netdev, rt_bool_t is_up)
{
    int shmid = channel_compose_cmd2(UNET_NETDEV_SET_STATUS, netdev, (void *)(size_t)is_up, 0);
    channel_cmd_send_recv(unet_channel, (void *)(size_t)shmid);
    lwp_shmrm(shmid);
}

void netdev_low_level_set_link_status(void *netdev, rt_bool_t is_up)
{
    int shmid = channel_compose_cmd2(UNET_NETDEV_SET_LINKSTATUS, netdev, (void *)(size_t)is_up, 0);
    channel_cmd_send(unet_channel, (void *)(size_t)shmid);
}

void netdev_low_level_set_dhcp_status(void *netdev, rt_bool_t is_enable)
{
    int shmid = channel_compose_cmd2(UNET_NETDEV_SET_DHCP, netdev, (void *)(size_t)is_enable, 0);
    channel_cmd_send(unet_channel, (void *)(size_t)shmid);
}

void netdev_low_level_set_dns_server(void *netdev, uint8_t dns_num, const ip_addr_t *dns_server)
{
    int shmid;
    struct channel_cmd *cmd;

    shmid = channel_compose_cmd3(UNET_NETDEV_SET_DNS, netdev, (void *)(size_t)dns_num,
            (void *)(size_t)CHANNEL_CMD_OFFSET, sizeof(ip_addr_t));
    if (shmid < 0)
        return;

    cmd = lwp_shmat(shmid, NULL);
    rt_memcpy((void *)(size_t)cmd + (size_t)cmd->argv[2], dns_server, sizeof(ip_addr_t));
    lwp_shmdt(cmd);

    channel_cmd_send_recv(unet_channel, (void *)(size_t)shmid);
    lwp_shmrm(shmid);
}

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
    stack_channel = rt_channel_open(chn_name, O_CREAT | O_EXCL);
    if (stack_channel < 0) return 1;    /* initialization has been done */

    /* If data_channel already exists, something must be wrong, fix it */
    data_channel  = rt_channel_open(data_name, O_CREAT | O_EXCL);
    if (data_channel < 0) goto close_stack_channel;

    /* During execution, stack_channel and data_channel are created and opened
     * only once when initialized. However, unet_channel might be opened many
     * times: first opened when initialized, then opened and closed each time we
     * attach or detach a network device. */
    unet_channel = rt_channel_open("unet", O_RDWR);
    if (unet_channel < 0) goto close_data_channel;

    /* attach ip stack in unet
     * UNET_TCPIP_STACK_ATTACH with
     * channel name offset
     * data channel name offset
     * -- data --
     * stack_channel_name
     * stack_data_channel_name
     */
    int shmid = channel_compose_cmd2(UNET_TCPIP_STACK_ATTACH, NULL, NULL, strlen(chn_name) + 1 +
        strlen(data_name) + 1);
    struct channel_cmd *cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
    if (cmd)
    {
        cmd->argv[0] = (void *)(size_t)(CHANNEL_CMD_OFFSET);
        cmd->argv[1] = (void *)(size_t)(CHANNEL_CMD_OFFSET  + strlen(chn_name) + 1);

        uint8_t *ptr = (uint8_t*)cmd + CHANNEL_CMD_OFFSET;
        strcpy((char*)ptr, chn_name);
        ptr = (uint8_t*)cmd + (CHANNEL_CMD_OFFSET  + strlen(chn_name) + 1);
        strcpy((char*)ptr, data_name);

        lwp_shmdt(cmd);
    }

    int ret = (int)(size_t)channel_cmd_send_recv(unet_channel, (void *)(size_t)shmid);
    lwp_shmrm(shmid);

    if (ret < 0)
    {
        printf("attach stack failed!\n");
        goto close_unet_channel;
    }

    /* start the TCPIP thread */
    lwip_system_init();
    return 0;

close_unet_channel:
    rt_channel_close(unet_channel);
    data_channel = -1;
close_data_channel:
    rt_channel_close(data_channel);
    data_channel = -1;
close_stack_channel:
    rt_channel_close(stack_channel);
    stack_channel = -1;
    return -1;      /* initialization fails */
}

static void stack_data_input(void* parameter)
{
    struct channel_cmd *cmd;
    const char *name;

    while (1)
    {
        int shmid = (int)(size_t)channel_cmd_recv(data_channel);
        if (shmid >= 0)
        {
            cmd = lwp_shmat(shmid, NULL);
            switch (cmd->cmd)
            {
            case UNET_SRV_DATA_INPUT:
            {
                struct netif *netif = (struct netif*)cmd->argv[1];
                int length = (int)(size_t)cmd->argv[2];
                uint8_t *buffer = (uint8_t*)(cmd + 1);

                if (netif == NULL)
                {
                    printf("NULL netif\n");
                    break;
                }
                
                struct pbuf *p = pbuf_alloc(PBUF_RAW, MAX_ETHERNET_FRAME, PBUF_POOL);
                if (p)
                {
                    /* copy buffer */
                    pbuf_take(p, buffer, length);
                    /* notify to stack */
                    if (netif->input(p, netif) != ERR_OK)
                    {
                        printf("netif->input failed\n");
                        pbuf_free(p);
                        p = NULL;
                    }
                    lwp_shmdt(cmd);
                    channel_cmd_reply(data_channel, (void *)(size_t)0);
                }
                else
                {
                    printf("%s pbuf alloc failed\n",__func__);
                    lwp_shmdt(cmd);
                    channel_cmd_reply(data_channel, (void *)(size_t)-1);
                }
                break;
            }
            case UNET_NETDEV_REQ_ATTACH:
            {
                //static_ip = (int)(size_t)cmd->argv[0];
                name = CHANNEL_CMD_DATA(cmd);
                eth_attach(name);
                lwp_shmdt(cmd);
                lwp_shmrm(shmid);
                break;
            }
            case UNET_NETDEV_REQ_DETACH:
            {
                name = CHANNEL_CMD_DATA(cmd);
                eth_deattach(name);
                lwp_shmdt(cmd);
                lwp_shmrm(shmid);
                break;
            }
            default:
                break;
            }
        }
    }
}
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
    int socket, len, result,old_socket;
    struct sockaddr *psockaddr;
    socklen_t socklen;
    socklen_t *psocklen;
    struct hostent *phostent;

    int domain, type, protocol;

    u32_t flags;

    void *data;
    size_t size;

    socklen_t tolen, *fromlen;
    char *pname;

    const char *nodename;
    const char *servname;
    const struct addrinfo *hints;
    struct addrinfo *u_ai;

    struct channel_cmd *cmd;
    struct lwip_sock *sock = RT_NULL;

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
            case UNET_SRV_SET_HW_STATUS:    /* NETIF_FLAG_UP */
            {
                struct netif *netif = cmd->argv[1];
                int updown = (int)(size_t)cmd->argv[2];
                if (updown)
                    netif_set_up(netif);
                else
                    netif_set_down(netif);

                lwp_shmdt(cmd);
                lwp_shmrm(shmid);
                break;
            }

            case UNET_SRV_SET_ADDR_INFO:    /* set addrinfo */
            {
                struct netif *netif = cmd->argv[1];

                if (cmd->argv[2])
                    netif_set_ipaddr(netif, (void *)(size_t)cmd + (size_t)cmd->argv[2]);
                if (cmd->argv[3])
                    netif_set_netmask(netif, (void *)(size_t)cmd + (size_t)cmd->argv[3]);
                if (cmd->argv[4])
                    netif_set_gw(netif, (void *)(size_t)cmd + (size_t)cmd->argv[4]);

                lwp_shmdt(cmd);
                lwp_shmrm(shmid);
                break;
            }

            case UNET_SRV_SET_DHCP:         /* set dhcp */
            {
                void *netdev = cmd->argv[0];
                struct netif *netif = cmd->argv[1];
                int enabled = (int)(size_t)cmd->argv[2];
                if (enabled)
                {
                    /* if this interface uses DHCP, start the DHCP client */
                    dhcp_start(netif);
                    netdev_low_level_set_dhcp_status(netdev, enabled);
                }
                else
                {
                    dhcp_stop(netif);
                    netdev_low_level_set_dhcp_status(netdev, enabled);
                }

                lwp_shmdt(cmd);
                lwp_shmrm(shmid);
                break;
            }

            case UNET_SRV_SET_DNS_SERVER:   /* set dns server */
                break;

            case UNET_SRV_SET_DEFAULT:      /* set default interface */
            {
                struct netif *netif = cmd->argv[1];
                netif_set_default(netif);

                lwp_shmdt(cmd);
                lwp_shmrm(shmid);
                break;
            }

            case UNET_SRV_NETSTAT:
                break;

            case UNET_SRV_PING: /* ping */
            {
                ip_addr_t target_addr;
                size_t data_len;
                size_t timeout;
                struct netdev_ping_resp resp;

                data_len = (size_t)cmd->argv[1];
                timeout  = (size_t)cmd->argv[2];
                memcpy(&target_addr, (void *)(size_t)(cmd + 1), sizeof(ip_addr_t));

                int ret = lwip_netdev_ping(&target_addr, data_len, timeout, &resp);
                if (ret == 0)
                {
                    cmd->argv[0] = (void *)(size_t)CHANNEL_CMD_OFFSET;
                    memcpy((void *)(size_t)(cmd + 1), &(resp.ip_addr), sizeof(ip_addr_t));
                    cmd->argv[1] = (void *)(size_t)resp.data_len;
                    cmd->argv[2] = (void *)(size_t)resp.ttl;
                    cmd->argv[3] = (void *)(size_t)resp.ticks;

                    channel_cmd_reply(stack_channel, (void *)(size_t)0);
                }
                else
                {
                    channel_cmd_reply(stack_channel, (void *)(size_t)-1);
                }

                lwp_shmdt(cmd);
                break;
            }

            /* handle socket requests */
            case UNET_SRV_CMD_SOCKET:
                domain = (int)(size_t)cmd->argv[0];
                type = (int)(size_t)cmd->argv[1];
                protocol = (int)(size_t)cmd->argv[2];
                socket = lwip_socket(domain, type, protocol);
                cmd->argv[0] = get_socket(socket);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)socket);
                break;

            case UNET_SRV_CMD_CLOSE:
                socket = (int)(size_t)cmd->argv[0];

                cmd->argv[0] = get_socket(socket);

                result = lwip_close(socket);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_BIND:
                socket = (int)(size_t)cmd->argv[0];
                psockaddr = (void *)(size_t)cmd + UNET_CMD_OFFSET;
                len = (int)(size_t)cmd->argv[2];

                result = lwip_bind(socket, psockaddr, len);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_LISTEN:
                socket = (int)(size_t)cmd->argv[0];
                socket = lwip_listen(socket, (int)(size_t)cmd->argv[1]);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)socket);
                break;

            case UNET_SRV_CMD_CONNECT:
                socket = (int)(size_t)cmd->argv[0];
                psockaddr = (void *)(size_t)cmd + UNET_CMD_OFFSET;
                len = (int)(size_t)cmd->argv[2];

                result = lwip_connect(socket, psockaddr, len);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_ACCEPT:
                old_socket = (int)(size_t)cmd->argv[0];
                psockaddr = (void *)(size_t)cmd + (size_t)cmd->argv[1];
                socket = lwip_accept(old_socket, psockaddr, (socklen_t *)&cmd->argv[2]);
                cmd->argv[0] = get_socket(socket);
                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)socket);
                break;

            case UNET_SRV_CMD_SENDTO:
                socket = (int)(size_t)cmd->argv[0];
                data = (void *)(size_t)cmd + (size_t)cmd->argv[1];
                size = (size_t)cmd->argv[2];
                flags = (int)(size_t)cmd->argv[3];
                psockaddr = (void *)(size_t)cmd + (size_t)cmd->argv[4];
                tolen = (socklen_t)(size_t)cmd->argv[5];

                lwip_send_count++;
                if(tolen  == 0)
                {
                    result = lwip_sendto(socket, data, size, flags, RT_NULL, RT_NULL);
                }
                else
                {
                    result = lwip_sendto(socket, data, size, flags, psockaddr, tolen);
                }
                if(result <= 0)
                {
                    rt_kprintf("%s line %d sendto error\n",__func__,__LINE__);
                }
                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_RECVFROM:
                socket = (int)(size_t)cmd->argv[0];
                data = (void *)(size_t)cmd + (size_t)cmd->argv[1];
                size = (size_t)(size_t)cmd->argv[2];
                flags = (int)(size_t)cmd->argv[3];

                psockaddr = (void *)(size_t)cmd + (size_t)cmd->argv[4];
                fromlen = (socklen_t *)(size_t)&cmd->argv[5];
                sock = get_socket(socket);
                if(cmd->argv[5] == RT_NULL)
                {
                    result = lwip_recvfrom(socket, data, size, flags, RT_NULL, RT_NULL);
                }
                else
                {
                    result = lwip_recvfrom(socket, data, size, flags , psockaddr, fromlen);
                }

                /* *RT-Thread* In user mode, we never block the function. */
                if (access_is_blocking(flags, sock) && result < 0)
                {
                    struct timeval timeout;
                    socklen_t timelen = sizeof(struct timeval);
                    lwip_getsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, &timelen);

                    result = -2;        /* try again */
                    cmd->argv[0] = sock;
                    cmd->argv[1] = (void *)(size_t)(timeout.tv_sec * 1000 + (timeout.tv_usec + 999) / 1000);
                }
                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;


            case UNET_SRV_CMD_GETSOCKOPT:
                socket = (int)(size_t)cmd->argv[0];
                int level = (int)(size_t)cmd->argv[1];
                int opt = (int)(size_t)cmd->argv[2];
                void *optval = (void *)(size_t)cmd + (size_t)cmd->argv[3];
                psocklen = (socklen_t *)&cmd->argv[4];

                result = lwip_getsockopt(socket, level, opt, optval, psocklen);
                RT_ASSERT(*psocklen < UNET_RECV_DATA_MAXLEN);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_SETSOCKOPT:
                socket = (int)(size_t)cmd->argv[0];
                level = (int)(size_t)cmd->argv[1];
                opt = (int)(size_t)cmd->argv[2];
                optval = (void *)(size_t)cmd + (size_t)cmd->argv[3];
                socklen = (socklen_t)(size_t)cmd->argv[4];

                result = lwip_setsockopt(socket, level, opt, optval, socklen);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_SHUTDOWN:
                socket = (int)(size_t)cmd->argv[0];

                result = lwip_shutdown(socket, (int)(size_t)cmd->argv[1]);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_GETPEERNAME:
                socket = (int)(size_t)cmd->argv[0];
                psockaddr = (void *)(size_t)cmd + (size_t)cmd->argv[1];
                psocklen = (socklen_t *)&cmd->argv[2];

                result = lwip_getpeername(socket, psockaddr, psocklen);
                RT_ASSERT(*psocklen < UNET_RECV_DATA_MAXLEN);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_GETSOCKNAME:
                socket = (int)(size_t)cmd->argv[0];
                psockaddr = (void *)(size_t)cmd + (size_t)cmd->argv[1];
                psocklen = (socklen_t *)&cmd->argv[2];

                result = lwip_getsockname(socket, psockaddr, psocklen);
                RT_ASSERT(*psocklen < UNET_RECV_DATA_MAXLEN);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_FCNTL:
                socket = (int)(size_t)cmd->argv[0];
                result = lwip_fcntl(socket, (int)(size_t)cmd->argv[1], (int)(size_t)cmd->argv[2]);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_IOCTL:
                socket = (int)(size_t)cmd->argv[0];
                result = lwip_ioctl(socket, (int)(size_t)cmd->argv[1], (int *)&cmd->argv[2]);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_GETHOSTBYNAME:
                pname = (void *)(size_t)cmd + UNET_CMD_OFFSET;
                phostent = lwip_gethostbyname(pname);
                if (phostent)
                    *((ip_addr_t *) &cmd->argv[0]) = *((ip_addr_t *) phostent->h_addr);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, phostent);
                break;

            case UNET_SRV_CMD_GETADDRINFO:
                nodename = (const char *)cmd + (size_t)cmd->argv[0];
                servname = (const char *)cmd + (size_t)cmd->argv[1];

                if(servname[0] == 0)
                {
                    servname = NULL;
                }
                hints = (const struct addrinfo *)((void *)(size_t)cmd + (size_t)cmd->argv[2]);

                /* store the pointer to the structure 'addrinfo' in user mode
                 * into the 4th argument */
                result = lwip_getaddrinfo(nodename, servname, hints, &u_ai);

                if (result == 0)
                {
                    rt_memcpy((void *)(size_t)cmd + (size_t)cmd->argv[3], u_ai, sizeof(*u_ai));
                    cmd->argv[3] = u_ai;

                    rt_memcpy((void *)(size_t)cmd + (size_t)cmd->argv[4], u_ai->ai_addr, sizeof(struct sockaddr));
                }
                else
                {
                    result = -1;
                }
                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)result);
                break;

            case UNET_SRV_CMD_FREEADDRINFO:
                u_ai = cmd->argv[0];
                lwip_freeaddrinfo(u_ai);

                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, u_ai);
                break;

            case UNET_SRV_CMD_POLL:
                /* arguments: maxfd, *readset, *writeset, *exceptset, *timeout */
                socket = (int)(size_t)cmd->argv[0];
                int mask = 0;
                sock = lwip_tryget_socket(socket);
                if (sock != NULL)
                {
    #if LWIP_VERSION >= 0x20100ff
                    if ((void*)(sock->lastdata.pbuf) || sock->rcvevent)
    #else
                    if ((void *)(sock->lastdata) || sock->rcvevent)
    #endif
                    {
                        mask |= POLLIN;
                    }
                    if (sock->sendevent)
                    {
                        mask |= POLLOUT;
                    }
                    if (sock->errevent)
                    {
                        mask |= POLLERR;
                        /* clean error event */
                        sock->errevent = 0;
                    }
                }
                /* Note, the actual socket is 'maxfd - 1'. */
                cmd->argv[0] = get_socket(socket);
                lwp_shmdt(cmd);
                unet_cmd_reply(stack_channel, (void *)(size_t)mask);
                break;

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
            netdev_list_init();
            printf(" ...succeeded!\n");

            rt_thread_t tid = rt_thread_create("ipdata", stack_data_input, NULL, 8192,
                25, 10);            /* handle the input data */
            if (tid) rt_thread_startup(tid);
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

