/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-02-27     bernard      fix the re-work issue.
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "workqueue.h"

static void _delayed_work_timeout_handler(void *parameter);

static rt_err_t _workqueue_submit_work(struct rt_workqueue *queue, struct rt_work *work)
{
    // // rt_base_t level;

    // level = rt_hw_interrupt_disable();
    if (work->flags & RT_WORK_STATE_PENDING)
    {
        // // rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    if (queue->work_current == work)
    {
        // // rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }

    /* NOTE: the work MUST be initialized firstly */
    rt_list_remove(&(work->list));

    rt_list_insert_after(queue->work_list.prev, &(work->list));
    work->flags |= RT_WORK_STATE_PENDING;

    /* whether the workqueue is doing work */
    if (queue->work_current == RT_NULL)
    {
        // rt_hw_interrupt_enable(level);
        /* resume work thread */
        rt_thread_resume(queue->work_thread);
        rt_schedule();
    }
    else
    {
        // rt_hw_interrupt_enable(level);
    }

    return RT_EOK;
}

static rt_err_t _workqueue_cancel_work(struct rt_workqueue *queue, struct rt_work *work)
{
    // rt_base_t level;

    // level = rt_hw_interrupt_disable();
    if (queue->work_current == work)
    {
        // rt_hw_interrupt_enable(level);
        return -RT_EBUSY;
    }
    rt_list_remove(&(work->list));
    work->flags &= ~RT_WORK_STATE_PENDING;
    // rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t _workqueue_cancel_delayed_work(struct rt_work *work)
{
    // rt_base_t level;
    int ret = RT_EOK;

    if (!work->workqueue)
    {
        ret = -EINVAL;
        goto __exit;
    }

    if (work->flags & RT_WORK_STATE_PENDING)
    {
        /* Remove from the queue if already submitted */
        ret = _workqueue_cancel_work(work->workqueue, work);
        if (ret)
        {
            goto __exit;
        }
    }
    else
    {
        if (work->flags & RT_WORK_STATE_SUBMITTING)
        {
            // level = rt_hw_interrupt_disable();
            rt_timer_stop(&(work->timer));
            rt_timer_detach(&(work->timer));
            work->flags &= ~RT_WORK_STATE_SUBMITTING;
            // rt_hw_interrupt_enable(level);
        }
    }

    // level = rt_hw_interrupt_disable();
    /* Detach from workqueue */
    work->workqueue = RT_NULL;
    work->flags &= ~(RT_WORK_STATE_PENDING);
    // rt_hw_interrupt_enable(level);

__exit:
    return ret;
}

static rt_err_t _workqueue_submit_delayed_work(struct rt_workqueue *queue,
        struct rt_work *work, rt_tick_t ticks)
{
    // rt_base_t level;
    rt_err_t ret = RT_EOK;

    /* Work cannot be active in multiple queues */
    if (work->workqueue && work->workqueue != queue)
    {
        ret = -RT_EINVAL;
        goto __exit;
    }

    /* Cancel if work has been submitted */
    if (work->workqueue == queue)
    {
        ret = _workqueue_cancel_delayed_work(work);
        if (ret < 0)
        {
            goto __exit;
        }
    }

    // level = rt_hw_interrupt_disable();
    /* Attach workqueue so the timeout callback can submit it */
    work->workqueue = queue;
    // rt_hw_interrupt_enable(level);

    if (!ticks)
    {
        /* Submit work if no ticks is 0 */
        ret = _workqueue_submit_work(work->workqueue, work);
    }
    else
    {
        // level = rt_hw_interrupt_disable();
        /* Add timeout */
        work->flags |= RT_WORK_STATE_SUBMITTING;
        rt_timer_init(&(work->timer), "work", _delayed_work_timeout_handler, work, ticks,
                      RT_TIMER_FLAG_ONE_SHOT | RT_TIMER_FLAG_SOFT_TIMER);
        // rt_hw_interrupt_enable(level);
        rt_timer_start(&(work->timer));
    }

__exit:
    return ret;
}

static void _delayed_work_timeout_handler(void *parameter)
{
    struct rt_work *delayed_work;
    // rt_base_t level;

    delayed_work = (struct rt_work *)parameter;
    // level = rt_hw_interrupt_disable();
    rt_timer_stop(&(delayed_work->timer));
    rt_timer_detach(&(delayed_work->timer));
    delayed_work->flags &= ~RT_WORK_STATE_SUBMITTING;
    delayed_work->type &= ~RT_WORK_TYPE_DELAYED;
    // rt_hw_interrupt_enable(level);
    _workqueue_submit_work(delayed_work->workqueue, delayed_work);
}

rt_err_t rt_workqueue_submit_work(struct rt_workqueue *queue, struct rt_work *work, rt_tick_t time)
{
    RT_ASSERT(queue != RT_NULL);
    RT_ASSERT(work != RT_NULL);

    if (time > 0)
    {
        work->type |= RT_WORK_TYPE_DELAYED;
    }

    if (work->type & RT_WORK_TYPE_DELAYED)
    {
        return _workqueue_submit_delayed_work(queue, work, time);
    }
    else
    {
        return _workqueue_submit_work(queue, work);
    }
}

void rt_delayed_work_init(struct rt_delayed_work *work, void (*work_func)(struct rt_work *work,
                          void *work_data), void *work_data)
{
    rt_work_init(&work->work, work_func, work_data);
}

static struct rt_workqueue *sys_workq;

rt_err_t rt_work_submit(struct rt_work *work, rt_tick_t time)
{
    return rt_workqueue_submit_work(sys_workq, work, time);
}