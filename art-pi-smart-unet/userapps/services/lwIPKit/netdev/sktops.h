/*
 * Copyright (c) 2011-2020, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-12     quanzhao     the first version
 */
#ifndef __UNET_H__
#define __UNET_H__

#include <rtthread.h>
#include <rtdef.h>

#include <lwip/sockets.h>   /* socklen_t */
#include <lwip/netdb.h>     /* lwip_gethostbyname */

int unet_socket(int domain, int type, int protocol);
int unet_close(int socket);
int unet_bind(int socket, const struct sockaddr *name, socklen_t namelen);
int unet_listen(int socket, int backlog);
int unet_connect(int socket, const struct sockaddr *name, socklen_t namelen);
int unet_accept(int socket, struct sockaddr *addr, socklen_t *addrlen);
int unet_sendto(int socket, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen);
int unet_recvfrom(int socket, void *mem, size_t size, int flags, struct sockaddr *from, socklen_t *fromlen);
int unet_getsockopt(int socket, int level, int optname, void *optval, socklen_t *optlen);
int unet_setsockopt(int socket, int level, int optname, const void *optval, socklen_t optlen);
int unet_shutdown(int socket, int how);
int unet_getpeername(int socket, struct sockaddr *name, socklen_t *namelen);
int unet_getsockname(int socket, struct sockaddr *name, socklen_t *namelen);
int unet_fcntl(int socket, int cmd, int val);
int unet_ioctl(int socket, long cmd, void *argp);
struct hostent* unet_gethostbyname(const char *name);
int unet_gethostbyname_r(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop);
struct hostent* unet_gethostbyname(const char *name);
int unet_gethostbyname_r(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop);
int unet_getaddrinfo(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res);
void unet_freeaddrinfo(struct addrinfo *ai);

/*
 * Interfaces to the wait queue associated with a socket in kernel. Each
 * operation that might block must hang in the queue in kernel.
 */
// int sock_wqueue_delete(void *sock);
// int sock_wqueue_add(void *sock);
// int sock_wqueue_suspend(void *sock, int ms);
// rt_wqueue_t *sock_wqueue_find(void *sock);

#endif  /* __UNET_H__ */
