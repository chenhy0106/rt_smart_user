/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <sys/time.h>
#include <rtdevice.h>

#ifdef RT_USING_DEVICE
int gettimeofday(struct timeval *tp, void *ignore)
{
    time_t time;
    rt_device_t device;

    device = rt_device_find("rtc");
    RT_ASSERT(device != RT_NULL);

    rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time);
    if (tp != RT_NULL)
    {
        tp->tv_sec = time;
        tp->tv_usec = 0;
    }

    return time;
}
#endif

time_t time(time_t *t)
{
    time_t time_now = 0;

#ifdef RT_USING_RTC
    static rt_device_t device = RT_NULL;

    /* optimization: find rtc device only first. */
    if (device == RT_NULL)
    {
        device = rt_device_find("rtc");
    }

    /* read timestamp from RTC device. */
    if (device != RT_NULL)
    {
        if (rt_device_open(device, 0) == RT_EOK)
        {
            rt_device_control(device, RT_DEVICE_CTRL_RTC_GET_TIME, &time_now);
            rt_device_close(device);
        }
    }
#endif /* RT_USING_RTC */

    /* if t is not NULL, write timestamp to *t */
    if (t != RT_NULL)
    {
        *t = time_now;
    }

    return time_now;
}

RT_WEAK clock_t clock(void)
{
    return rt_tick_get();
}
