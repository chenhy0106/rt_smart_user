#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rtthread.h>
#include <channel.h>
#include <unet.h>

#include "drv_eth.h"
#include "netdev.h"
#include "usocket.h"

extern int lwip_system_init(void);
extern void sal_init(void);
extern int dfs_init(void);

static int stack_channel = -1;  /* implement system calls */
const char *chn_name = "lwIPKit";

/*
 * lwIPKit could be initialized at most once. If the stack channel exists, we
 * assume lwIPKit has been set up and no further actions should be taken. Three
 * cases are distinguished by the return value:
 *  0: initialization completes successfully, further actions can be carried on
 *  1: initialization has been done before, we could do anything but another
 *  initialization
 */
int stack_init(void)
{
    /* stack channel as a flag whether the stack has been initialized */
    stack_channel = rt_channel_open(chn_name, O_CREAT);
    if (stack_channel < 0) return 1;    /* initialization has been done */

    /* start the TCPIP thread */
    lwip_system_init();
    return 0;
}

int stack_run(void)
{
    int socket, len, result;
    struct sockaddr *psockaddr;
    int domain, type, protocol;
    socklen_t socklen;
    socklen_t tolen, *fromlen;

    u32_t flags;

    void *data;
    size_t size;

    struct channel_cmd *cmd;

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

            default :
                break;
            }
        }
    }

    return 0;
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

int main(int argc, char **argv)
{
    int initialized = 0;

    /* we want to run lwIPKit as a server */
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
            printf(" ...succeeded!\n");
            printf("lwIPKit: init eth dev...");
            initialized = imx6ul_eth_init();
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
                printf(" ...succeeded\n");
                dfs_init();
                sal_init();
            }

            stack_run();            /* handle network requests, never return */
        }
    }

    lwipkit_usage();
    return -1;
}

