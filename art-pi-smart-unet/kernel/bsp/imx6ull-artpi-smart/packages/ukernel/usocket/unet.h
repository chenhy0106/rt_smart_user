/*
 * Copyright (c) 2011-2020, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-12     quanzhao     the first version
 */
#ifndef __UNET_H__
#define __UNET_H__

#include <rtthread.h>
#include <rtdef.h>
#include <ipc_srv.h>

#define UNET_RECV_DATA_MAXLEN    (4096-WORKLOAD_START)

/*
 * UNET requests the user network stack to change the network state. All the
 * operations are handled by the user network stack, no reply is required.
 */
#define UNET_SRV_SET_HW_STATUS      1
#define UNET_SRV_SET_ADDR_INFO      2
#define UNET_SRV_SET_DNS_SERVER     3
#define UNET_SRV_SET_DHCP           4
#define UNET_SRV_PING               5
#define UNET_SRV_NETSTAT            6
#define UNET_SRV_SET_DEFAULT        7

#define UNET_SRV_DATA_INPUT         8   /* data received */

/*
 * The user network requests UNET to change the netdev state, so that network
 * state in the user network stack keeps identical with the one in kernel.
 */
#define UNET_NETDEV_SETIPADDR       10
#define UNET_NETDEV_SETNETMASK      11
#define UNET_NETDEV_SETGW           12
#define UNET_NETDEV_SET_LINKSTATUS  13
#define UNET_NETDEV_SET_DNS         14
#define UNET_NETDEV_SET_STATUS      15
#define UNET_NETDEV_SET_ADDRINFO    16
#define UNET_NETDEV_SET_DHCP        17

/* UNET socket interfaces, implemented by the user network stack */
#define UNET_SRV_CMD_SOCKET         20
#define UNET_SRV_CMD_CLOSE          21
#define UNET_SRV_CMD_BIND           22
#define UNET_SRV_CMD_LISTEN         23
#define UNET_SRV_CMD_CONNECT        24
#define UNET_SRV_CMD_ACCEPT         25
#define UNET_SRV_CMD_SENDTO         26
#define UNET_SRV_CMD_RECVFROM       27
#define UNET_SRV_CMD_GETSOCKOPT     28
#define UNET_SRV_CMD_SETSOCKOPT     29
#define UNET_SRV_CMD_SHUTDOWN       30
#define UNET_SRV_CMD_GETPEERNAME    31
#define UNET_SRV_CMD_GETSOCKNAME    32
#define UNET_SRV_CMD_FCNTL          33
#define UNET_SRV_CMD_IOCTL          34

/* the retured structure includes other pointers */
#define UNET_SRV_CMD_GETHOSTBYNAME  35
#define UNET_SRV_CMD_GETHOSTBYNAME_R    36

#define UNET_SRV_CMD_GETADDRINFO    37
#define UNET_SRV_CMD_FREEADDRINFO   38
#define UNET_SRV_CMD_POLL           39
#endif  /* __UNET_H__ */
