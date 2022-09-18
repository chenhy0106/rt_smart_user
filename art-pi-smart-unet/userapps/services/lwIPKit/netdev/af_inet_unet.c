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

