/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: GPL-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     Jesven       the first version
 * 2019-10-01     Bernard      code cleanup
 */

#include <sys/rtt_syscall.h>
#include <rtthread.h>

rt_err_t rt_device_init(rt_device_t dev)
{
    return syscall(_NRSYS_rt_device_init, dev);
}

rt_err_t rt_device_register(rt_device_t dev,
        const char *name,
        rt_uint16_t flags)
{
    return syscall(_NRSYS_rt_device_register, dev, name, flags);
}

rt_err_t rt_device_control(rt_device_t dev, int cmd, void *arg)
{
    return syscall(_NRSYS_rt_device_control, dev, cmd, arg);
}

rt_device_t rt_device_find(const char *name)
{
    return (rt_device_t)syscall(_NRSYS_rt_device_find, name);
}

rt_err_t rt_device_open(rt_device_t dev, rt_uint16_t oflag)
{
    return syscall(_NRSYS_rt_device_open, dev, oflag);
}

rt_err_t rt_device_close(rt_device_t dev)
{
    return syscall(_NRSYS_rt_device_close, dev);
}

rt_size_t rt_device_read(rt_device_t dev,
        rt_off_t    pos,
        void       *buffer,
        rt_size_t   size)
{
    return syscall(_NRSYS_rt_device_read, dev, pos, buffer, size);
}

rt_size_t rt_device_write(rt_device_t dev,
        rt_off_t    pos,
        const void *buffer,
        rt_size_t   size)
{
    return syscall(_NRSYS_rt_device_write, dev, pos, buffer, size);;
}
