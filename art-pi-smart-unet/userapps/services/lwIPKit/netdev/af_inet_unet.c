/*
 * Copyright (c) 2011-2020, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     ChenYong     First version
 */

#include <rtthread.h>

#include "sktops.h"

#ifdef SAL_USING_POSIX
#include <dfs_poll.h>
#include <libc/libc_fdset.h>
#endif

#include "sal.h"
// #include "af_inet.h"

#include "netdev.h"

int inet_ioctlsocket(int socket, long cmd, void *arg)
{
    switch (cmd)
    {
    case F_GETFL:
    case F_SETFL:
        return unet_fcntl(socket, cmd, (int)(unsigned long) arg);

    default:
        return unet_ioctl(socket, cmd, arg);
    }
}

// extern int unet_get_wakeup_event_cnt(int fd,rt_uint64_t *event_cnt);
// #ifdef SAL_USING_POSIX
// static int inet_poll(struct dfs_fd *file, struct rt_pollreq *req)
// {
//     int mask;
//     int socket = (int)(unsigned long)file->fnode->data;
//     int lwip_fd = 0;
//     struct sal_socket *sal_sock;
//     int shmid;
//     struct unet_cmd *unet_cmd;
//     rt_uint64_t old_wakeup_event_cnt;
//     rt_uint64_t new_wakeup_event_cnt;

//     sal_sock = sal_get_socket(socket);
//     if(!sal_sock)
//     {
//         return -1;
//     }
//     lwip_fd = (int)(unsigned long)(size_t)sal_sock->user_data;

//     /* arguments: maxfd, *readset, *writeset, *exceptset, *timeout */
//     shmid = compose_cmd1(UNET_SRV_CMD_POLL, (void *)(unsigned long)lwip_fd, 0);
//     if (shmid < 0)
//     {
//         rt_kprintf("%s get shmid %d error\n",__func__,shmid);
//         return -1;
//     }

//     unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
//     unet_get_wakeup_event_cnt(lwip_fd,&old_wakeup_event_cnt);
//     mask = (int)(unsigned long) unet_cmd_send_recv(unet_get_stack_channel(), (void *)(unsigned long)shmid);

//     /*
//      * During the unet_cmd_send_recv function call, the wake-up event may occur. 
//      * If an update is detected, call unet_cmd_send_recv function again to get last event
//      */
//     unet_get_wakeup_event_cnt(lwip_fd,&new_wakeup_event_cnt);
//     if(new_wakeup_event_cnt > old_wakeup_event_cnt)
//     {
//         unet_cmd->argv[0] = (void *)(unsigned long)(lwip_fd);
//         mask = (int)(unsigned long) unet_cmd_send_recv(unet_get_stack_channel(), (void *)(unsigned long)shmid);
//     }

//     rt_wqueue_t *wq = sock_wqueue_find(unet_cmd->argv[0]);

//     lwp_shmrm(shmid);
    
//     if (wq)
//         rt_poll_add(wq, req);

//     return mask;
// }
// #endif

static const struct sal_socket_ops unet_socket_ops =
{
    unet_socket,
    unet_close,
    unet_bind,
    unet_listen,
    unet_connect,
    //inet_accept,
    unet_accept,
    unet_sendto,
    unet_recvfrom,
    unet_getsockopt,
    //TODO fix on 1.4.1
    unet_setsockopt,
    unet_shutdown,
    unet_getpeername,
    //inet_getsockname,
    unet_getsockname,
    inet_ioctlsocket,
#ifdef SAL_USING_POSIX
    // inet_poll,
    RT_NULL,
#endif
};

static const struct sal_netdb_ops unet_netdb_ops =
{
    unet_gethostbyname,
    unet_gethostbyname_r,
    unet_getaddrinfo,
    unet_freeaddrinfo,
};

static const struct sal_proto_family unet_inet_family =
{
    AF_INET,
    AF_INET,
    &unet_socket_ops,
    &unet_netdb_ops,
};

/* Set lwIP network interface device protocol family information */
int sal_unet_netdev_set_pf_info(struct netdev *netdev)
{
    RT_ASSERT(netdev);

    netdev->sal_user_data = (void *)(unsigned long) &unet_inet_family;
    return 0;
}

