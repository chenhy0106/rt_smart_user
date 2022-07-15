/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier:GPL-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     Jesven       the first version
 * 2019-10-01     Bernard      code cleanup
 */
#include <bits/errno.h>
#include "syscall.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/rtt_syscall.h>
#include <sys/socket.h>
#include <netdb.h>

#include <dfs_posix.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <time.h>

int closesocket(int s)
{
    return (int)syscall(_NRSYS_closesocket, s);
}

int getaddrinfo(const char *restrict host, const char *restrict serv, const struct addrinfo *restrict hint, struct addrinfo **restrict res)
{
    struct addrinfo *ret = NULL;

    ret = (struct addrinfo *) malloc(sizeof(struct addrinfo) + sizeof(struct sockaddr));
    if (ret)
    {
        ret->ai_addr = (struct sockaddr *)(ret + 1);

        /* invoke syscall */
        int result = syscall(_NRSYS_getaddrinfo, host, serv, hint, ret);
        if (result == 0)
        {
            *res = ret;
        }
    }

    return 0;
}

void freeaddrinfo(struct addrinfo *p)
{
    /* p->ai_canonname, p->ai_next should be NULL. */
    free(p);
}

int gethostbyname2_r(const char *name, int af, struct hostent *ret,
                    char *buf, size_t buflen,
                    struct hostent **result, int *err)
{
    return syscall(_NRSYS_gethostbyname2_r, name, af, ret, buf, buflen, result, err);
}

/* set non-blocking */
int setnonblocking(int fd)
{
    int old_option = fcntl( fd, F_GETFL, 0);
    int new_option = old_option | O_NONBLOCK;
    if (fcntl(fd, F_SETFL, new_option) == -1)
    {
        printf("Set noblocking error!\n");
        return 1;
    }
    return old_option;
}

int socketpair(int domain, int type, int protocol, int sv[2])
{
    int listenfd = -1, acceptfd = -1, clientfd = -1;
    /* for server, accept, client */
    struct sockaddr_in saddr, aaddr, caddr;
    socklen_t len = sizeof(struct sockaddr_in);
    int on = 1;
    int fdopt;
    int rt_port;

    /* for select */
    int maxfdp = 0;
    int rst;
    fd_set rfd;
    struct timeval timeout = {0, 1000};

    /* server socket */
    if ((listenfd = socket(domain, type, protocol)) < 0)
    {
        printf("Create listenfd socket error: %s(errno: %d)\n", strerror(errno), errno);
        return -1;
    }
    /* non-blocking */
    setnonblocking(listenfd);

    /* get random port: 5001~65001 */
    srand((unsigned)time(NULL));
    rt_port = rand() % 60000 + 5001;

    /* bind and listen */
    memset(&saddr, 0, sizeof(saddr));
    memset(&aaddr, 0, sizeof(aaddr));
    saddr.sin_family = domain;
    saddr.sin_port = htons(rt_port);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(int)) < 0)
    {
        perror("Setsockopt reuseadd failed");
        goto __exit;
    }

    if (bind(listenfd, (struct sockaddr*)&saddr, sizeof(saddr)) == -1)
    {
        printf("Bind socket error: %s(errno: %d), fd=%d\n", strerror(errno), errno, listenfd);
        goto __exit;
    }

    if (listen(listenfd, 10) == -1)
    {
        printf("Listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        goto __exit;
    }

    /* client socket */
    if ((clientfd = socket(domain, type, protocol)) < 0)
    {
        printf("Create clientfd socket error: %s(errno: %d)\n", strerror(errno), errno);
        goto __exit;
    }

    /* non-blocking */
    fdopt = setnonblocking(clientfd);
    /* client connect */
    memset(&caddr, 0, sizeof(caddr));
    caddr.sin_family = domain;
    caddr.sin_port =htons(rt_port);
    caddr.sin_addr.s_addr=htonl(INADDR_ANY);
    connect(clientfd, (struct sockaddr*)&caddr, sizeof(caddr));

    /* do select */
    FD_ZERO(&rfd);
    FD_SET(listenfd, &rfd);
    FD_SET(clientfd, &rfd);
    maxfdp = listenfd > clientfd ? listenfd+1 : clientfd+1;
    rst = select(maxfdp, &rfd, NULL, NULL, &timeout);
    switch(rst)
    {
    case -1:
        perror("select error");
        goto __exit;
        break;
    case 0:
        perror("continue");
        break;
    default:
        if (FD_ISSET(listenfd, &rfd))
        {
            if ((acceptfd = accept(listenfd, (struct sockaddr*)&caddr, &len)) > 0)
            {
                close(listenfd);
                /* set old optional back */
                fcntl(clientfd, F_SETFL, fdopt);
                sv[0] = clientfd;
                sv[1] = acceptfd;
            }

            return 0;
        }
    }

__exit:
    if (listenfd >= 0) close(listenfd);
    if (clientfd >= 0) close(clientfd);

    return -1;
}
