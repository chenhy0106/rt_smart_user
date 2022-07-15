/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier:GPL-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     Jesven       the first version
 * 2019-10-01     Bernard      code cleanup
 */

#include <sys/rtt_syscall.h>
#include <rtthread.h>

int rt_channel_open(const char *name, int flags)
{
    return syscall(_NRSYS_channel_open, name, flags);
}

rt_err_t rt_channel_close(int fd)
{
    return syscall(_NRSYS_channel_close, fd);
}

rt_err_t rt_channel_send_recv(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret)
{
    return syscall(_NRSYS_channel_send_recv_timeout, fd, data, data_ret, RT_WAITING_FOREVER);
}

rt_err_t rt_channel_send_recv_timeout(int fd, rt_channel_msg_t data, rt_channel_msg_t data_ret, rt_int32_t time)
{
    return syscall(_NRSYS_channel_send_recv_timeout, fd, data, data_ret, time);
}

rt_err_t rt_channel_send(int fd, rt_channel_msg_t data)
{
    return syscall(_NRSYS_channel_send, fd, data);
}

rt_err_t rt_channel_reply(int fd, rt_channel_msg_t data)
{
    return syscall(_NRSYS_channel_reply, fd, data);
}

rt_err_t rt_channel_recv(int fd, rt_channel_msg_t data)
{
    return syscall(_NRSYS_channel_recv_timeout, fd, data, RT_WAITING_FOREVER);
}

rt_err_t rt_channel_recv_timeout(int fd, rt_channel_msg_t data, rt_int32_t time)
{
    return syscall(_NRSYS_channel_recv_timeout, fd, data, time);
}

rt_err_t rt_channel_peek(int fd, rt_channel_msg_t data)
{
    return syscall(_NRSYS_channel_recv_timeout, fd, data, 0);
}
