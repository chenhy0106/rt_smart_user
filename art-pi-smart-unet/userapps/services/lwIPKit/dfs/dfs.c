#include "dfs.h"
#include "dfs_file.h"

/* device filesystem lock */
static struct rt_mutex fslock;
static struct rt_mutex fdlock;

static struct dfs_fdtable _fdtab;
static int  fd_alloc(struct dfs_fdtable *fdt, int startfd);

/**
 * @addtogroup DFS
 */

/*@{*/

/**
 * this function will initialize device file system.
 */
int dfs_init(void)
{
    static rt_bool_t init_ok = RT_FALSE;

    if (init_ok)
    {
        rt_kprintf("dfs already init.\n");
        return 0;
    }

    /* init fnode hash table */
    dfs_fnode_mgr_init();

    /* clean fd table */
    memset(&_fdtab, 0, sizeof(_fdtab));

    /* create device filesystem lock */
    rt_mutex_init(&fslock, "fslock", RT_IPC_FLAG_FIFO);
    rt_mutex_init(&fdlock, "fdlock", RT_IPC_FLAG_FIFO);

    init_ok = RT_TRUE;

    return 0;
}

/**
 * this function will lock device file system.
 *
 * @note please don't invoke it on ISR.
 */
void dfs_lock(void)
{
    rt_err_t result = -RT_EBUSY;

    while (result == -RT_EBUSY)
    {
        result = rt_mutex_take(&fslock, RT_WAITING_FOREVER);
    }

    if (result != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

void dfs_fd_lock(void)
{
    rt_err_t result = -RT_EBUSY;

    while (result == -RT_EBUSY)
    {
        result = rt_mutex_take(&fdlock, RT_WAITING_FOREVER);
    }

    if (result != RT_EOK)
    {
        RT_ASSERT(0);
    }
}

/**
 * this function will lock device file system.
 *
 * @note please don't invoke it on ISR.
 */
void dfs_unlock(void)
{
    rt_mutex_release(&fslock);
}

void dfs_fd_unlock(void)
{
    rt_mutex_release(&fdlock);
}

static int fd_slot_expand(struct dfs_fdtable *fdt, int fd)
{
    int nr;
    int index;
    struct dfs_fd **fds = NULL;

    if (fd < fdt->maxfd)
    {
        return fd;
    }
    if (fd >= DFS_FD_MAX)
    {
        return -1;
    }

    nr = ((fd + 4) & ~3);
    if (nr > DFS_FD_MAX)
    {
        nr = DFS_FD_MAX;
    }
    fds = (struct dfs_fd **)rt_realloc(fdt->fds, nr * sizeof(struct dfs_fd *));
    if (!fds)
    {
        return -1;
    }

    /* clean the new allocated fds */
    for (index = fdt->maxfd; index < nr; index++)
    {
        fds[index] = NULL;
    }
    fdt->fds   = fds;
    fdt->maxfd = nr;

    return fd;
}

static int fd_slot_alloc(struct dfs_fdtable *fdt, int startfd)
{
    int idx;

    /* find an empty fd slot */
    for (idx = startfd; idx < (int)fdt->maxfd; idx++)
    {
        if (fdt->fds[idx] == RT_NULL)
        {
            return idx;
        }
    }

    idx = fdt->maxfd;
    if (idx < startfd)
    {
        idx = startfd;
    }
    if (fd_slot_expand(fdt, idx) < 0)
    {
        return -1;
    }
    return idx;
}

static int fd_alloc(struct dfs_fdtable *fdt, int startfd)
{
    int idx;
    struct dfs_fd *fd = NULL;

    idx = fd_slot_alloc(fdt, startfd);

    /* allocate  'struct dfs_fd' */
    if (idx < 0)
    {
        return -1;
    }
    fd = (struct dfs_fd *)rt_calloc(1, sizeof(struct dfs_fd));
    if (!fd)
    {
        return -1;
    }
    fd->ref_count = 1;
    fd->magic = DFS_FD_MAGIC;
    fd->fnode = NULL;
    fdt->fds[idx] = fd;

    return idx;
}

/**
 * @ingroup Fd
 * This function will allocate a file descriptor.
 *
 * @return -1 on failed or the allocated file descriptor.
 */
int fdt_fd_new(struct dfs_fdtable *fdt)
{
    int idx;

    /* lock filesystem */
    dfs_fd_lock();

    /* find an empty fd entry */
    idx = fd_alloc(fdt, DFS_STDIO_OFFSET);

    /* can't find an empty fd entry */
    if (idx < 0)
    {
        rt_kprintf("DFS fd new is failed! Could not found an empty fd entry.");
    }

    dfs_fd_unlock();
    return idx;
}

int fd_new(void)
{
    struct dfs_fdtable *fdt = NULL;

    fdt = dfs_fdtable_get();
    return fdt_fd_new(fdt);
}

/**
 * @ingroup Fd
 *
 * This function will return a file descriptor structure according to file
 * descriptor.
 *
 * @return NULL on on this file descriptor or the file descriptor structure
 * pointer.
 */

struct dfs_fd *fdt_fd_get(struct dfs_fdtable* fdt, int fd)
{
    struct dfs_fd *d;

    if (fd < 0 || fd >= (int)fdt->maxfd)
    {
        return NULL;
    }

    dfs_fd_lock();
    d = fdt->fds[fd];

    /* check dfs_fd valid or not */
    if ((d == NULL) || (d->magic != DFS_FD_MAGIC))
    {
        dfs_fd_unlock();
        return NULL;
    }

    dfs_fd_unlock();

    return d;
}

struct dfs_fd *fd_get(int fd)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    return fdt_fd_get(fdt, fd);
}

/**
 * @ingroup Fd
 *
 * This function will put the file descriptor.
 */
void fdt_fd_release(struct dfs_fdtable* fdt, int fd)
{
    struct dfs_fd *fd_slot = NULL;

    RT_ASSERT(fdt != NULL);

    dfs_fd_lock();

    if ((fd < 0) || (fd >= fdt->maxfd))
    {
        dfs_fd_unlock();
        return;
    }

    fd_slot = fdt->fds[fd];
    if (fd_slot == NULL)
    {
        dfs_fd_unlock();
        return;
    }
    fdt->fds[fd] = NULL;

    /* check fd */
    RT_ASSERT(fd_slot->magic == DFS_FD_MAGIC);

    fd_slot->ref_count--;

    /* clear this fd entry */
    if (fd_slot->ref_count == 0)
    {
        struct dfs_fnode *fnode = fd_slot->fnode;
        if (fnode)
        {
            fnode->ref_count--;
        }
        rt_free(fd_slot);
    }
    dfs_fd_unlock();
}

void fd_release(int fd)
{
    struct dfs_fdtable *fdt;

    fdt = dfs_fdtable_get();
    fdt_fd_release(fdt, fd);
}

/**
 * This function will get the file descriptor table of current process.
 */
struct dfs_fdtable *dfs_fdtable_get(void)
{
    return &_fdtab;
}
