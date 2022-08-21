/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-02-17     Bernard      First version
 * 2018-05-17     ChenYong     Add socket abstraction layer
 */

#include <dfs.h>
#include <dfs_file.h>
#include <dfs_poll.h>
#include "dfs_net.h"

#include "sal_socket.h"

int accept_internal(int s, struct sockaddr *addr, socklen_t *addrlen)
{
    int new_socket = -1;
    int socket = dfs_net_getsocket(s);

    new_socket = sal_accept(socket, addr, addrlen);
    if (new_socket != -1)
    {
        /* this is a new socket, create it in file system fd */
        int fd;
        struct dfs_fd *d;

        /* allocate a fd */
        fd = fd_new();
        if (fd < 0)
        {
            sal_closesocket(new_socket);
            return -ENOMEM;
        }

        d = fd_get(fd);
        if(d)
        {
            /* this is a socket fd */
            d->fnode = (struct dfs_fnode *)rt_malloc(sizeof(struct dfs_fnode));
            if (!d->fnode)
            {
                /* release fd */
                fd_release(fd);
                return -ENOMEM;
            }
            rt_memset(d->fnode, 0, sizeof(struct dfs_fnode));
            rt_list_init(&d->fnode->list);

            d->fnode->type = FT_SOCKET;
            d->fnode->path = NULL;
            d->fnode->fullpath = NULL;
            d->fnode->ref_count = 1;
            d->fnode->fops = dfs_net_get_fops();
            d->flags = O_RDWR; /* set flags as read and write */
            d->fnode->size = 0;
            d->pos = 0;

            /* set socket to the data of dfs_fd */
            d->fnode->data = (void *)(size_t)new_socket;

            return fd;
        }

        sal_closesocket(new_socket);
        return -ENOMEM;
    }

    return -1;
}

int bind_internal(int s, const struct sockaddr *name, socklen_t namelen)
{
    int socket = dfs_net_getsocket(s);

#ifdef SAL_USING_AF_UNIX
    struct sockaddr_in server_addr = {0};
    if (name->sa_family == AF_UNIX)
    {
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(514);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        return sal_bind(socket, (struct sockaddr *)&server_addr, namelen);
    }
#endif /* SAL_USING_AF_UNIX */

    return sal_bind(socket, name, namelen);
}

int connect_internal(int s, const struct sockaddr *name, socklen_t namelen)
{
    int socket = dfs_net_getsocket(s);

#ifdef SAL_USING_AF_UNIX
    struct sockaddr_in server_addr = {0};
    if (name->sa_family == AF_UNIX)
    {
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(514);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        return sal_connect(socket, (struct sockaddr *)&server_addr, namelen);
    }
#endif /* SAL_USING_AF_UNIX */

    return sal_connect(socket, name, namelen);
}

int setsockopt_internal(int s, int level, int optname, const void *optval, socklen_t optlen)
{
    int socket = dfs_net_getsocket(s);

    return sal_setsockopt(socket, level, optname, optval, optlen);
}

int listen_internal(int s, int backlog)
{
    int socket = dfs_net_getsocket(s);

    return sal_listen(socket, backlog);
}


int recv_internal(int s, void *mem, size_t len, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_recvfrom(socket, mem, len, flags, NULL, NULL);
}

int recvfrom_internal(int s, void *mem, size_t len, int flags,
             struct sockaddr *from, socklen_t *fromlen)
{
    int socket = dfs_net_getsocket(s);

    return sal_recvfrom(socket, mem, len, flags, from, fromlen);
}

int send_internal(int s, const void *dataptr, size_t size, int flags)
{
    int socket = dfs_net_getsocket(s);

    return sal_sendto(socket, dataptr, size, flags, NULL, 0);
}

int sendto_internal(int s, const void *dataptr, size_t size, int flags,
           const struct sockaddr *to, socklen_t tolen)
{
    int socket = dfs_net_getsocket(s);

    return sal_sendto(socket, dataptr, size, flags, to, tolen);
}

int socket_internal(int domain, int type, int protocol)
{
    /* create a BSD socket */
    int fd;
    int socket;
    struct dfs_fd *d;

    /* allocate a fd */
    fd = fd_new();
    if (fd < 0)
    {
        return -ENOMEM;
    }
    d = fd_get(fd);
    d->fnode = (struct dfs_fnode *)rt_malloc(sizeof(struct dfs_fnode));
    if (!d->fnode)
    {
        /* release fd */
        fd_release(fd);
        return -ENOMEM;
    }

#ifdef SAL_USING_AF_UNIX
    if (domain == AF_UNIX)
    {
        domain = AF_INET;
    }
#endif /* SAL_USING_AF_UNIX */
    /* create socket  and then put it to the dfs_fd */
    socket = sal_socket(domain, type, protocol);
    if (socket >= 0)
    {
        rt_memset(d->fnode, 0, sizeof(struct dfs_fnode));
        rt_list_init(&d->fnode->list);
        /* this is a socket fd */
        d->fnode->type = FT_SOCKET;
        d->fnode->path = NULL;
        d->fnode->fullpath = NULL;
        d->fnode->ref_count = 1;
        d->fnode->fops = dfs_net_get_fops();

        d->flags = O_RDWR; /* set flags as read and write */
        d->fnode->size = 0;
        d->pos = 0;

        /* set socket to the data of dfs_fd */
        d->fnode->data = (void *)(size_t)socket;
    }
    else
    {
        rt_free(d->fnode);
        /* release fd */
        fd_release(fd);
        return -ENOMEM;
    }

    return fd;
}