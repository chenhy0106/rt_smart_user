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
#include <stdio.h>
#include <stdlib.h>

#include <sys/rtt_syscall.h>
#include <rtthread.h>

#ifndef RT_TIMER_SKIP_LIST_LEVEL
#define RT_TIMER_SKIP_LIST_LEVEL 1
#endif

#define SIG_HW_TIMER 31

/* hardware timer */
static rt_timer_t hw_timer = RT_NULL;
static void rt_hw_timer_update(void);
static rt_mutex_t mutex = RT_NULL;
static rt_sem_t sem = RT_NULL;

static rt_list_t rt_soft_timer_list[RT_TIMER_SKIP_LIST_LEVEL];

static void _rt_timer_init(rt_timer_t timer,
                           void (*timeout)(void *parameter),
                           void      *parameter,
                           rt_tick_t  time,
                           rt_uint8_t flag)
{
    int i;

    /* set flag */
    timer->parent.flag  = flag;

    /* set deactivated */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    timer->timeout_func = timeout;
    timer->parameter    = parameter;

    timer->timeout_tick = 0;
    timer->init_tick    = time;

    /* initialize timer list */
    for (i = 0; i < RT_TIMER_SKIP_LIST_LEVEL; i++)
    {
        rt_list_init(&(timer->row[i]));
    }
}

/* the fist timer always in the last row */
static rt_tick_t rt_timer_list_next_timeout(rt_list_t timer_list[])
{
    struct rt_timer *timer;

    if (rt_list_isempty(&timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1]))
        return RT_TICK_MAX;

    timer = rt_list_entry(timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1].next,
                          struct rt_timer, row[RT_TIMER_SKIP_LIST_LEVEL - 1]);

    return timer->timeout_tick;
}

rt_inline void _rt_timer_remove(rt_timer_t timer)
{
    int i;

    for (i = 0; i < RT_TIMER_SKIP_LIST_LEVEL; i++)
    {
        rt_list_remove(&timer->row[i]);
    }
}

#if RT_DEBUG_TIMER
static int rt_timer_count_height(struct rt_timer *timer)
{
    int i, cnt = 0;

    for (i = 0; i < RT_TIMER_SKIP_LIST_LEVEL; i++)
    {
        if (!rt_list_isempty(&timer->row[i]))
            cnt++;
    }
    return cnt;
}

void rt_timer_dump(rt_list_t timer_heads[])
{
    rt_list_t *list;

    for (list = timer_heads[RT_TIMER_SKIP_LIST_LEVEL - 1].next;
         list != &timer_heads[RT_TIMER_SKIP_LIST_LEVEL - 1];
         list = list->next)
    {
        struct rt_timer *timer = rt_list_entry(list,
                                               struct rt_timer,
                                               row[RT_TIMER_SKIP_LIST_LEVEL - 1]);
        printf("%d", rt_timer_count_height(timer));
    }
    printf("\n");
}
#endif

/**
 * @addtogroup Clock
 */

/**@{*/

/**
 * This function will initialize a timer, normally this function is used to
 * initialize a static timer object.
 *
 * @param timer the static timer object
 * @param name the name of timer
 * @param timeout the timeout function
 * @param parameter the parameter of timeout function
 * @param time the tick of timer
 * @param flag the flag of timer
 */
void rt_timer_init(rt_timer_t  timer,
                   const char *name,
                   void (*timeout)(void *parameter),
                   void       *parameter,
                   rt_tick_t   time,
                   rt_uint8_t  flag)
{
    _rt_timer_init(timer, timeout, parameter, time, flag);
}

/**
 * This function will detach a timer from timer management.
 *
 * @param timer the static timer object
 *
 * @return the operation status, RT_EOK on OK; RT_ERROR on error
 */
rt_err_t rt_timer_detach(rt_timer_t timer)
{

    /* make sure take mutex */
    while(rt_mutex_take(mutex, RT_WAITING_FOREVER) != RT_EOK);

    _rt_timer_remove(timer);

    /* release mutex */
    rt_mutex_release(mutex);

    return RT_EOK;
}

/**
 * This function will create a timer
 *
 * @param name the name of timer
 * @param timeout the timeout function
 * @param parameter the parameter of timeout function
 * @param time the tick of timer
 * @param flag the flag of timer
 *
 * @return the created timer object
 */
rt_timer_t rt_timer_create(const char *name,
                           void (*timeout)(void *parameter),
                           void       *parameter,
                           rt_tick_t   time,
                           rt_uint8_t  flag)
{
    struct rt_timer *timer;

    /* allocate a timer object */
    timer = (struct rt_timer *)malloc(sizeof(struct rt_timer));
    if (timer == RT_NULL)
    {
        return RT_NULL;
    }

    _rt_timer_init(timer, timeout, parameter, time, flag);

    return timer;
}

/**
 * This function will delete a timer and release timer memory
 *
 * @param timer the timer to be deleted
 *
 * @return the operation status, RT_EOK on OK; RT_ERROR on error
 */
rt_err_t rt_timer_delete(rt_timer_t timer)
{

    /* make sure take mutex */
    while(rt_mutex_take(mutex, RT_WAITING_FOREVER) != RT_EOK);

    _rt_timer_remove(timer);

    /*free timer object */
    free(timer);

    /* release mutex */
    rt_mutex_release(mutex);

    return RT_EOK;
}

/**
 * This function will start the timer
 *
 * @param timer the timer to be started
 *
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_start(rt_timer_t timer)
{
    unsigned int row_lvl;
    rt_list_t *timer_list;
    rt_list_t *row_head[RT_TIMER_SKIP_LIST_LEVEL];
    unsigned int tst_nr;
    static unsigned int random_nr;

    /* make sure take mutex */
    while(rt_mutex_take(mutex, RT_WAITING_FOREVER) != RT_EOK);
    /* remove timer from list */
    _rt_timer_remove(timer);
    /* change status of timer */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
    /* release mutex */
    rt_mutex_release(mutex);

    /*
     * get timeout tick,
     * the max timeout tick shall not great than RT_TICK_MAX/2
     */
    timer->timeout_tick = rt_tick_get() + timer->init_tick;

    /* make sure take mutex */
    while(rt_mutex_take(mutex, RT_WAITING_FOREVER) != RT_EOK);

    /* insert timer to soft timer list */
    timer_list = rt_soft_timer_list;

    row_head[0]  = &timer_list[0];
    for (row_lvl = 0; row_lvl < RT_TIMER_SKIP_LIST_LEVEL; row_lvl++)
    {
        for (; row_head[row_lvl] != timer_list[row_lvl].prev;
             row_head[row_lvl]  = row_head[row_lvl]->next)
        {
            struct rt_timer *t;
            rt_list_t *p = row_head[row_lvl]->next;

            /* fix up the entry pointer */
            t = rt_list_entry(p, struct rt_timer, row[row_lvl]);

            /* If we have two timers that timeout at the same time, it's
             * preferred that the timer inserted early get called early.
             * So insert the new timer to the end the the some-timeout timer
             * list.
             */
            if ((t->timeout_tick - timer->timeout_tick) == 0)
            {
                continue;
            }
            else if ((t->timeout_tick - timer->timeout_tick) < RT_TICK_MAX / 2)
            {
                break;
            }
        }
        if (row_lvl != RT_TIMER_SKIP_LIST_LEVEL - 1)
            row_head[row_lvl + 1] = row_head[row_lvl] + 1;
    }

    /* Interestingly, this super simple timer insert counter works very very
     * well on distributing the list height uniformly. By means of "very very
     * well", I mean it beats the randomness of timer->timeout_tick very easily
     * (actually, the timeout_tick is not random and easy to be attacked). */
    random_nr++;
    tst_nr = random_nr;

    rt_list_insert_after(row_head[RT_TIMER_SKIP_LIST_LEVEL - 1],
                         &(timer->row[RT_TIMER_SKIP_LIST_LEVEL - 1]));
    for (row_lvl = 2; row_lvl <= RT_TIMER_SKIP_LIST_LEVEL; row_lvl++)
    {
        if (!(tst_nr & RT_TIMER_SKIP_LIST_MASK))
            rt_list_insert_after(row_head[RT_TIMER_SKIP_LIST_LEVEL - row_lvl],
                                 &(timer->row[RT_TIMER_SKIP_LIST_LEVEL - row_lvl]));
        else
            break;
        /* Shift over the bits we have tested. Works well with 1 bit and 2
         * bits. */
        tst_nr >>= (RT_TIMER_SKIP_LIST_MASK + 1) >> 1;
    }

    timer->parent.flag |= RT_TIMER_FLAG_ACTIVATED;

    /* release mutex */
    rt_mutex_release(mutex);

    /* update hardware timer */
    rt_hw_timer_update();

    return RT_EOK;
}

/**
 * This function will stop the timer
 *
 * @param timer the timer to be stopped
 *
 * @return the operation status, RT_EOK on OK, -RT_ERROR on error
 */
rt_err_t rt_timer_stop(rt_timer_t timer)
{
    if (!(timer->parent.flag & RT_TIMER_FLAG_ACTIVATED))
        return -RT_ERROR;

    /* make sure take mutex */
    while(rt_mutex_take(mutex, RT_WAITING_FOREVER) != RT_EOK);

    _rt_timer_remove(timer);

    /* release mutex */
    rt_mutex_release(mutex);

    /* change stat */
    timer->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;

    return RT_EOK;
}

/**
 * This function will get or set some options of the timer
 *
 * @param timer the timer to be get or set
 * @param cmd the control command
 * @param arg the argument
 *
 * @return RT_EOK
 */
rt_err_t rt_timer_control(rt_timer_t timer, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_TIMER_CTRL_GET_TIME:
        *(rt_tick_t *)arg = timer->init_tick;
        break;

    case RT_TIMER_CTRL_SET_TIME:
        timer->init_tick = *(rt_tick_t *)arg;
        break;

    case RT_TIMER_CTRL_SET_ONESHOT:
        timer->parent.flag &= ~RT_TIMER_FLAG_PERIODIC;
        break;

    case RT_TIMER_CTRL_SET_PERIODIC:
        timer->parent.flag |= RT_TIMER_FLAG_PERIODIC;
        break;

    case RT_TIMER_CTRL_GET_FUNC:
        *(void **)arg = timer->timeout_func;
        break;

    case RT_TIMER_CTRL_SET_FUNC:
        timer->timeout_func = (void (*)(void*))arg;
        break;

    case RT_TIMER_CTRL_GET_PARM:
        *(void **)arg = timer->parameter;
        break;

    case RT_TIMER_CTRL_SET_PARM:
        timer->parameter = arg;
        break;
    }

    return RT_EOK;
}

/**
 * This function will check timer list, if a timeout event happens, the
 * corresponding timeout function will be invoked.
 */
void rt_soft_timer_check(void)
{
    rt_tick_t current_tick;
    rt_list_t *n;
    struct rt_timer *t;

    RT_DEBUG_LOG(RT_DEBUG_TIMER, ("software timer check enter\n"));

    current_tick = rt_tick_get();

    /* make sure take mutex */
    while(rt_mutex_take(mutex, RT_WAITING_FOREVER) != RT_EOK);

    for (n = rt_soft_timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1].next;
         n != &(rt_soft_timer_list[RT_TIMER_SKIP_LIST_LEVEL - 1]);)
    {
        t = rt_list_entry(n, struct rt_timer, row[RT_TIMER_SKIP_LIST_LEVEL - 1]);

        /*
         * It supposes that the new tick shall less than the half duration of
         * tick max.
         */
        if ((current_tick - t->timeout_tick) < RT_TICK_MAX / 2)
        {
            /* move node to the next */
            n = n->next;

            /* remove timer from timer list firstly */
            _rt_timer_remove(t);

            /* release mutex */
            rt_mutex_release(mutex);
            /* call timeout function */
            t->timeout_func(t->parameter);

            /* re-get tick */
            current_tick = rt_tick_get();

            RT_DEBUG_LOG(RT_DEBUG_TIMER, ("current tick: %d\n", current_tick));

            /* make sure take mutex */
            while(rt_mutex_take(mutex, RT_WAITING_FOREVER) != RT_EOK);


            if ((t->parent.flag & RT_TIMER_FLAG_PERIODIC) &&
                    (t->parent.flag & RT_TIMER_FLAG_ACTIVATED))
            {
                /* start it */
                t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
                rt_timer_start(t);
            }
            else
            {
                /* stop timer */
                t->parent.flag &= ~RT_TIMER_FLAG_ACTIVATED;
            }
        }
        else break; /* not check anymore */
    }

    /* release mutex */
    rt_mutex_release(mutex);

    RT_DEBUG_LOG(RT_DEBUG_TIMER, ("software timer check leave\n"));
}

/* update hardware timer */
static void rt_hw_timer_update(void)
{
    rt_tick_t next_timeout;
    rt_tick_t current_tick;

    /* get the next timeout tick */
    next_timeout = rt_timer_list_next_timeout(rt_soft_timer_list);
    if (next_timeout == RT_TICK_MAX)
    {
        /* no software timer exist, return. */
        return;
    }

    /* get current tick */
    current_tick = rt_tick_get();

    if ((next_timeout - current_tick) < RT_TICK_MAX / 2)
    {
        syscall(_NRSYS_timer_stop, hw_timer);
        /* get the delta timeout tick */
        next_timeout = next_timeout - current_tick;
        syscall(_NRSYS_timer_control,
                hw_timer,
                RT_TIMER_CTRL_SET_TIME,
                &next_timeout);
        syscall(_NRSYS_timer_start, hw_timer);
    }
    return;
}

/* timer signal handler */
static void rt_thread_timer_handler(void)
{
    /* update hardware timer */
    rt_hw_timer_update();
    /* check software timer */
    rt_soft_timer_check();
}

static void timer_thread_entry(void* parameter)
{
    while (1)
    {
        rt_err_t ret;
        ret = rt_sem_take(sem, RT_WAITING_FOREVER);
        if (ret != RT_EOK)
        {
            break;
        }
        rt_thread_timer_handler();
    }
}

void rt_system_timer_init(rt_uint32_t timer_stack_size)
{
    int i;
    rt_thread_t tid;

    if (!sem)
    {
        sem = rt_sem_create("u_timer", 0, RT_IPC_FLAG_FIFO);
    }

    if (!mutex)
    {
        mutex = rt_mutex_create("utm_mutex", RT_IPC_FLAG_FIFO);
    }

    for (i = 0;
         i < sizeof(rt_soft_timer_list) / sizeof(rt_soft_timer_list[0]);
         i++)
    {
        rt_list_init(rt_soft_timer_list + i);
    }

    /* initial hardware timer */
    if (!hw_timer)
    {
        hw_timer = (rt_timer_t)syscall(_NRSYS_timer_create,
                "u_timer",
                sem->data, //SIG_HW_TIMER,
                0,
                RT_TIMER_FLAG_ONE_SHOT|RT_TIMER_FLAG_HARD_TIMER);
    }

    if (timer_stack_size < 4096)
    {
        timer_stack_size = 4096;
    }

    tid = rt_thread_create("u_timer", timer_thread_entry, RT_NULL,
            timer_stack_size, 2, 10);
    if (tid)
    {
        rt_thread_startup(tid);
    }
}

/**@}*/
