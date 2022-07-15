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
#include <rtdevice.h>

void rt_completion_init(struct rt_completion *completion)
{
    if (completion && completion->flag == 0)
    {
        completion->flag = 0x5A5A;
        completion->wait_event = rt_event_create("completion", RT_IPC_FLAG_FIFO);
    }
}

rt_err_t rt_completion_wait(struct rt_completion *completion,
    rt_int32_t timeout)
{
    rt_err_t ret;
    rt_uint32_t recv = 0;

    ret = rt_event_recv(completion->wait_event, 0x01, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, timeout, &recv);

    return ret;
}

void rt_completion_done(struct rt_completion *completion)
{
    rt_event_send(completion->wait_event, 0x01);
}
