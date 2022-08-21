/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2005-01-26     Bernard      The first version.
 */

#ifndef __DFS_FILE_H__
#define __DFS_FILE_H__

#include "dfs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct rt_pollreq;

struct dfs_file_ops
{
    int (*close)    (struct dfs_fd *fd);
    int (*ioctl)    (struct dfs_fd *fd, int cmd, void *args);
    int (*read)     (struct dfs_fd *fd, void *buf, size_t count);
    int (*write)    (struct dfs_fd *fd, const void *buf, size_t count);

    int (*poll)     (struct dfs_fd *fd, struct rt_pollreq *req);
};

/* file descriptor */
#define DFS_FD_MAGIC     0xfdfd

struct dfs_fnode
{
    uint16_t type;               /* Type (regular or socket) */

    char *path;                  /* Name (below mount point) */
    char *fullpath;              /* Full path is hash key */
    int ref_count;               /* Descriptor reference count */
    rt_list_t list;              /* The node of fnode hash table */

    const struct dfs_file_ops *fops;
    uint32_t flags;              /* self flags, is dir etc.. */

    size_t   size;               /* Size in bytes */
    void *data;                  /* Specific file system data */
};

struct dfs_fd
{
    uint16_t magic;              /* file descriptor magic number */
    uint32_t flags;              /* Descriptor flags */
    int ref_count;               /* Descriptor reference count */
    off_t    pos;                /* Current file position */
    struct dfs_fnode *fnode;     /* file node struct */
    void *data;                  /* Specific fd data */
};

void dfs_fnode_mgr_init(void);

#ifdef __cplusplus
}
#endif

#endif
