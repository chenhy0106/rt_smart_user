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
#include <rthw.h>
#include <rtthread.h>
#include <pthread.h>

void __pthread_init_run(void (*enter)(void *parameter), void *parameter);

rt_thread_t rt_thread_find(char *name)
{
    return (rt_thread_t)syscall(_NRSYS_rt_thread_find, name);
}

struct rt_thread_startup_ucontext
{
    void (*entry)(void *parameter);
    void *parameter;
};

static void rt_thread_user_entry(void *arg)
{
    struct rt_thread_startup_ucontext *ucontext;
    void (*entry)(void *parameter);
    void *parameter;

    ucontext = (struct rt_thread_startup_ucontext *)arg;
    entry = ucontext->entry;
    parameter = ucontext->parameter;
    rt_free(ucontext);

    __pthread_init_run(entry, parameter);
}

rt_thread_t rt_thread_create(const char *name,
        void (*entry)(void *parameter),
        void       *parameter,
        rt_uint32_t stack_size,
        rt_uint8_t  priority,
        rt_uint32_t tick)
{
    rt_thread_t thread;
    void * arg[] = {(void *)name, (void*)entry, (void*)parameter, (void*)(size_t)stack_size, (void*)(size_t)priority, (void*)(size_t)tick};
    struct rt_thread_startup_ucontext *ucontext;

    ucontext = rt_malloc(sizeof *ucontext);
    if (!ucontext)
    {
        return RT_NULL;
    }
    ucontext->entry = entry;
    ucontext->parameter = parameter;
    arg[1] = rt_thread_user_entry;
    arg[2] = ucontext;

    thread = (rt_thread_t)syscall(_NRSYS_thread_create, arg);
    if (!thread)
    {
        rt_free(ucontext);
    }
    return thread;
}

rt_err_t rt_thread_startup(rt_thread_t thread)
{
    return syscall(_NRSYS_thread_startup, thread);
}

rt_thread_t rt_thread_self(void)
{
    return (rt_thread_t)syscall(_NRSYS_thread_self);
}

rt_err_t rt_thread_delete(rt_thread_t thread)
{
    return syscall(_NRSYS_thread_delete, thread);
}

void rt_enter_critical(void)
{
    syscall(_NRSYS_enter_critical);
}

void rt_exit_critical(void)
{
    syscall(_NRSYS_exit_critical);
}

int cacheflush(void *addr, int size, int cache)
{
    return syscall(_NRSYS_cacheflush, addr, size, cache);
}

