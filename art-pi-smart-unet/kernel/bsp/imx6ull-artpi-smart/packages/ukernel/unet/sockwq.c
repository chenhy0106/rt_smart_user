/*
 * Copyright (c) 2011-2020, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-12     quanzhao     the first version
 */
#include <rtdef.h>
#include <rtthread.h>
#include <lwp_avl.h>
#include <ipc/waitqueue.h>

static struct lwp_avl_struct *psockwq_tree = RT_NULL;
static struct rt_mutex sockwq_lock;

rt_err_t sock_wqueue_init(void)
{
    return rt_mutex_init(&sockwq_lock, "sockwq_lock", 0);
}

#define SOCK_WQUEUE_LOCK    do { rt_mutex_take(&sockwq_lock, RT_WAITING_FOREVER); } while(0)
#define SOCK_WQUEUE_UNLOCK  do { rt_mutex_release(&sockwq_lock); } while(0)

int sock_wqueue_add(void *sock)
{
    struct lwp_avl_struct *node;
    rt_wqueue_t *wq;

    /*
     * The argument sock should be a valid address of the socket structure. If
     * it is 0, the corresponding socket doesn't exist, don't bother to add it.
     */
    if (sock == 0) return -1;

    /* allocate a waitqueue for the sock */
    wq = (rt_wqueue_t *)rt_malloc(sizeof(rt_wqueue_t));
    if (!wq)
        return -1;
    rt_wqueue_init(wq);

    /* allocate a tree node for the sock */
    node = (struct lwp_avl_struct *)rt_malloc(sizeof(struct lwp_avl_struct));
    if (!node)
    {
        rt_free(wq);
        return -1;
    }
    memset(node, 0, sizeof(struct lwp_avl_struct));

    SOCK_WQUEUE_LOCK;
    if (lwp_avl_find((avl_key_t) sock, psockwq_tree))
    {
        SOCK_WQUEUE_UNLOCK;
        rt_free(wq);
        rt_free(node);
        return -1;    /* already exists */
    }

    /* add the node to the tree */
    node->avl_key = (avl_key_t) sock;
    node->data = (void*)wq;

    lwp_avl_insert(node, &psockwq_tree);
    SOCK_WQUEUE_UNLOCK;

    return 0;
}

int sock_wqueue_delete(void *sock)
{
    struct lwp_avl_struct *node;

    /*
     * The argument sock should be a valid address of the socket structure. If
     * it is 0, the corresponding socket doesn't exist, don't bother to remove
     * it.
     */
    if (sock == 0) return -1;

    SOCK_WQUEUE_LOCK;
    node = lwp_avl_find((avl_key_t) sock, psockwq_tree);
    if (!node)
    {
        SOCK_WQUEUE_UNLOCK;
        return -1;   /* not exists */
    }

    lwp_avl_remove(node, &psockwq_tree);
    SOCK_WQUEUE_UNLOCK;

    rt_free(node->data);    /* free the waitqueue */
    rt_free(node);
    return 0;
}

int sock_wqueue_suspend(void *sock, int ms)
{
    struct lwp_avl_struct *node;
    rt_wqueue_t *wq;

    if (!sock) return -1;

    SOCK_WQUEUE_LOCK;
    node = lwp_avl_find((avl_key_t) sock, psockwq_tree);
    SOCK_WQUEUE_UNLOCK;
    if (!node) return -1;   /* not exists */

    wq = (rt_wqueue_t *) node->data;
    RT_ASSERT(wq);

    return rt_wqueue_wait(wq, 0, ms);
}

int sock_wqueue_wakeup(void *sock)
{
    struct lwp_avl_struct *node;
    rt_wqueue_t *wq;

    if (!sock) return -1;

    SOCK_WQUEUE_LOCK;
    node = lwp_avl_find((avl_key_t) sock, psockwq_tree);
    SOCK_WQUEUE_UNLOCK;
    if (!node) return -1;   /* not exists */

    wq = (rt_wqueue_t *) node->data;
    RT_ASSERT(wq);

    rt_wqueue_wakeup(wq, 0);
    return 0;
}

rt_wqueue_t *sock_wqueue_find(void *sock)
{
    struct lwp_avl_struct *node;
    rt_wqueue_t *wq;

    if (!sock) return RT_NULL;

    SOCK_WQUEUE_LOCK;
    node = lwp_avl_find((avl_key_t) sock, psockwq_tree);
    SOCK_WQUEUE_UNLOCK;
    if (!node) return RT_NULL;   /* not exists */

    wq = (rt_wqueue_t *) node->data;

    return wq;
}
