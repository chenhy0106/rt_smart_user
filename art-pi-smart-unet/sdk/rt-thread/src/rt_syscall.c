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
#include <rthw.h>
#include <rtthread.h>
#include <string.h>
#include <time.h>

#include <dfs_fs.h>
#include <dfs_file.h>
#include <sys/rtt_syscall.h>

#define RT_USER_IPC_CREATE(ipc_type, ...)\
    do {\
        struct rt_user_ipc *ipc; \
\
        ipc = (struct rt_user_ipc*)malloc(sizeof *ipc);\
        if (!ipc)\
        {\
            return RT_NULL;\
        }\
        ipc->data = (void*)syscall(__VA_ARGS__);\
        if (ipc->data)\
        {\
            ipc->type = ipc_type;\
        }\
        else\
        {\
            free(ipc);\
            ipc = RT_NULL;\
        }\
        return ipc;\
    } while (0)

#define RT_USER_IPC_INIT(ipc, ipc_type, ...)\
    do {\
        if (!ipc)\
        {\
            return RT_EIO;\
        }\
        ipc->data = (void*)syscall(__VA_ARGS__);\
        if (ipc->data)\
        {\
            ipc->type = ipc_type;\
        }\
        else\
        {\
            return RT_ERROR;\
        }\
        return RT_EOK;\
    } while (0)

#define RT_USER_IPC_DELETE(ipc, ipc_type, sc_no)\
    do {\
        rt_err_t ret; \
        if (!ipc || !ipc->data)\
        {\
            return RT_EIO;\
        }\
        if (ipc->type != ipc_type)\
        {\
            return RT_EIO;\
        }\
        ret = (rt_err_t)syscall(sc_no, ipc->data);\
        if (ret != RT_EOK) \
        {\
            return ret;\
        }\
        free(ipc); \
        return RT_EOK;\
    } while (0)

#define RT_USER_IPC_DETACH(ipc, ipc_type, sc_no)\
    do {\
        rt_err_t ret; \
        if (!ipc || !ipc->data)\
        {\
            return RT_EIO;\
        }\
        if (ipc->type != ipc_type)\
        {\
            return RT_EIO;\
        }\
        ret = (rt_err_t)syscall(sc_no, ipc->data);\
        if (ret != RT_EOK) \
        {\
            return ret;\
        }\
        ipc->type = 0; \
        ipc->data = RT_NULL;\
        return RT_EOK;\
    } while (0)

#define RT_USER_IPC_CHECK(ipc, ipc_type)\
    do {\
        if (!ipc || !ipc->data)\
        {\
            return RT_EIO;\
        }\
        if (ipc->type != ipc_type)\
        {\
            return RT_EIO;\
        }\
    } while (0)

rt_mutex_t rt_mutex_create(const char *name, rt_uint8_t flag)
{
    RT_USER_IPC_CREATE(RT_Object_Class_Mutex, _NRSYS_mutex_create, name, flag);
}

rt_err_t rt_mutex_init(rt_mutex_t mutex, const char *name, rt_uint8_t flag)
{
    RT_USER_IPC_INIT(mutex, RT_Object_Class_Mutex, _NRSYS_mutex_create, name, flag);
}

rt_err_t rt_mutex_delete(rt_mutex_t mutex)
{
    RT_USER_IPC_DELETE(mutex, RT_Object_Class_Mutex, _NRSYS_mutex_delete);
}

rt_err_t rt_mutex_detach(rt_mutex_t mutex)
{
    RT_USER_IPC_DETACH(mutex, RT_Object_Class_Mutex, _NRSYS_mutex_delete);
}

rt_err_t rt_mutex_take(rt_mutex_t mutex, rt_int32_t time)
{
    RT_USER_IPC_CHECK(mutex, RT_Object_Class_Mutex);
    return syscall(_NRSYS_mutex_take, mutex->data, time);
}

rt_err_t rt_mutex_release(rt_mutex_t mutex)
{
    RT_USER_IPC_CHECK(mutex, RT_Object_Class_Mutex);
    return syscall(_NRSYS_mutex_release, mutex->data);
}

rt_sem_t rt_sem_create(const char *name, rt_uint32_t value, rt_uint8_t flag)
{
    RT_USER_IPC_CREATE(RT_Object_Class_Semaphore, _NRSYS_sem_create, name, value, flag);
}

rt_err_t rt_sem_init(rt_sem_t sem,
                     const char *name,
                     rt_uint32_t value,
                     rt_uint8_t  flag)
{
    RT_USER_IPC_INIT(sem, RT_Object_Class_Semaphore, _NRSYS_sem_create, name, value, flag);
}

rt_err_t rt_sem_delete(rt_sem_t sem)
{
    RT_USER_IPC_DELETE(sem, RT_Object_Class_Semaphore, _NRSYS_sem_delete);
}

rt_err_t rt_sem_detach(rt_sem_t sem)
{
    RT_USER_IPC_DETACH(sem, RT_Object_Class_Semaphore, _NRSYS_sem_delete);
}

rt_err_t rt_sem_release(rt_sem_t sem)
{
    RT_USER_IPC_CHECK(sem, RT_Object_Class_Semaphore);
    return syscall(_NRSYS_sem_release, sem->data);
}

rt_err_t rt_sem_take(rt_sem_t sem, rt_int32_t time)
{
    RT_USER_IPC_CHECK(sem, RT_Object_Class_Semaphore);
    return syscall(_NRSYS_sem_take, sem->data, time);
}

rt_mailbox_t rt_mb_create(const char *name, rt_size_t size, rt_uint8_t flag)
{
    RT_USER_IPC_CREATE(RT_Object_Class_MailBox, _NRSYS_mb_create, name, size, flag);
}

rt_err_t rt_mb_init(rt_mailbox_t mb,
                    const char  *name,
                    void        *msgpool,
                    rt_size_t    size,
                    rt_uint8_t   flag)
{
    RT_USER_IPC_INIT(mb, RT_Object_Class_MailBox, _NRSYS_mb_create, name, size, flag);
}


rt_err_t rt_mb_delete(rt_mailbox_t mb)
{
    RT_USER_IPC_DELETE(mb, RT_Object_Class_MailBox, _NRSYS_mb_delete);
}

rt_err_t rt_mb_detach(rt_mailbox_t mb)
{
    RT_USER_IPC_DETACH(mb, RT_Object_Class_MailBox, _NRSYS_mb_delete);
}

rt_err_t rt_mb_send_wait(rt_mailbox_t mb,
        rt_ubase_t   value,
        rt_int32_t   timeout)
{
    RT_USER_IPC_CHECK(mb, RT_Object_Class_MailBox);
    return syscall(_NRSYS_mb_send_wait, mb->data, value, timeout);
}

rt_err_t rt_mb_send(rt_mailbox_t mb, rt_ubase_t value)
{
    RT_USER_IPC_CHECK(mb, RT_Object_Class_MailBox);
    return syscall(_NRSYS_mb_send, mb->data, value);
}

rt_err_t rt_mb_recv(rt_mailbox_t mb, rt_ubase_t *value, rt_int32_t timeout)
{
    RT_USER_IPC_CHECK(mb, RT_Object_Class_MailBox);
    return syscall(_NRSYS_mb_recv, mb->data, value, timeout);
}

rt_mq_t rt_mq_create(const char *name,
                     rt_size_t   msg_size,
                     rt_size_t   max_msgs,
                     rt_uint8_t  flag)
{
    RT_USER_IPC_CREATE(RT_Object_Class_MessageQueue, _NRSYS_mq_create, name, msg_size, max_msgs, flag);
}

rt_err_t rt_mq_init(rt_mq_t mq,
                    const char *name,
                    void       *msgpool,
                    rt_size_t   msg_size,
                    rt_size_t   pool_size,
                    rt_uint8_t  flag)
{
    RT_USER_IPC_INIT(mq, RT_Object_Class_MessageQueue, _NRSYS_mq_create, name, msg_size, pool_size/msg_size, flag);
}

rt_err_t rt_mq_delete(rt_mq_t mq)
{
    RT_USER_IPC_DELETE(mq, RT_Object_Class_MessageQueue, _NRSYS_mq_delete);
}

rt_err_t rt_mq_detach(rt_mq_t mq)
{
    RT_USER_IPC_DETACH(mq, RT_Object_Class_MessageQueue, _NRSYS_mq_delete);
}

rt_err_t rt_mq_send(rt_mq_t mq, const void *buffer, rt_size_t size)
{
    RT_USER_IPC_CHECK(mq, RT_Object_Class_MessageQueue);
    return syscall(_NRSYS_mq_send, mq->data, buffer, size);
}

rt_err_t rt_mq_urgent(rt_mq_t mq, const void *buffer, rt_size_t size)
{
    RT_USER_IPC_CHECK(mq, RT_Object_Class_MessageQueue);
    return syscall(_NRSYS_mq_urgent, mq->data, buffer, size);
}

rt_err_t rt_mq_recv(rt_mq_t    mq,
                    void      *buffer,
                    rt_size_t  size,
                    rt_int32_t timeout)
{
    RT_USER_IPC_CHECK(mq, RT_Object_Class_MessageQueue);
    return syscall(_NRSYS_mq_recv, mq->data, buffer, size, timeout);
}

rt_event_t rt_event_create(const char *name, rt_uint8_t flag)
{
    RT_USER_IPC_CREATE(RT_Object_Class_Event, _NRSYS_event_create, name, flag);
}

rt_err_t rt_event_init(rt_event_t event, const char *name, rt_uint8_t flag)
{
    RT_USER_IPC_INIT(event, RT_Object_Class_Event, _NRSYS_event_create, name, flag);
}

rt_err_t rt_event_delete(rt_event_t event)
{
    RT_USER_IPC_DELETE(event, RT_Object_Class_Event, _NRSYS_event_delete);
}

rt_err_t rt_event_detach(rt_event_t event)
{
    RT_USER_IPC_DETACH(event, RT_Object_Class_Event, _NRSYS_event_delete);
}

rt_err_t rt_event_send(rt_event_t event, rt_uint32_t set)
{
    RT_USER_IPC_CHECK(event, RT_Object_Class_Event);
    return syscall(_NRSYS_event_send, event->data, set);
}

rt_err_t rt_event_recv(rt_event_t   event,
                       rt_uint32_t  set,
                       rt_uint8_t   opt,
                       rt_int32_t   timeout,
                       rt_uint32_t *recved)
{
    RT_USER_IPC_CHECK(event, RT_Object_Class_Event);
    return syscall(_NRSYS_event_recv, event->data, set, opt, timeout, recved);
}

rt_tick_t rt_tick_get(void)
{
    return (rt_tick_t)syscall(_NRSYS_rt_tick_get);
}

rt_err_t rt_thread_mdelay(rt_int32_t ms)
{
    return (rt_err_t)syscall(_NRSYS_rt_thread_mdelay, ms);
}

int lwp_shmget(size_t key, size_t size, int create)
{
    return (int)syscall(_NRSYS_shmget, key, size, create);
}

int lwp_shmrm(int id)
{
    return (int)syscall(_NRSYS_shmrm, id);
}

void* lwp_shmat(int id, void* shm_vaddr)
{
    return (void*)syscall(_NRSYS_shmat, id, shm_vaddr);
}

int lwp_shmdt(void* shm_vaddr)
{
    return (int)syscall(_NRSYS_shmdt, shm_vaddr);
}

int exec(char *filename, int argc, char **argv, char **envp)
{
    return (int)syscall(_NRSYS_exec, filename, argc, argv, envp);
}

int lwp_kill(pid_t pid, int sig)
{
    return (int)syscall(_NRSYS_kill, pid, sig);
}

int lwp_tkill(int tid, int sig)
{
    return (int)syscall(_NRSYS_tkill, tid, sig);
}

pid_t waitpid(pid_t pid, int *status, int options)
{
    return (int)syscall(_NRSYS_waitpid, pid, status, options);
}

rt_err_t rt_get_errno(void)
{
    return (rt_err_t)syscall(_NRSYS_rt_get_errno);
}
