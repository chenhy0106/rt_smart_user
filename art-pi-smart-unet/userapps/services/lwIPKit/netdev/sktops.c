/*
 * Copyright (c) 2011-2020, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-12     quanzhao     the first version
 */
#include <rtthread.h>

#include "sktops.h"

#define K_AI_ADDR_OFFSET (16)
rt_uint8_t k_ai_addr[K_AI_ADDR_OFFSET];

/*
 * The following functions implement the system calls propogated downwards from
 * SAL. They simply prepare the corresponding commands and send them to unet in
 * user mode and return the result back to SAL.
 */
/*
 * In the network stack implementation, the argument 'type' must NOT include any
 * socket options. To solve the issue, we do it separately in 2 steps.
 */
#define INTF_SOCK_NONBLOCK  04000
#define IMPL_SOCK_NONBLOCK  1
int unet_socket(int domain, int type, int protocol)
{
    int socket;

    /* filter-out socket options: SOCK_NONBLOCK & SOCK_CLOEXEC (not supported) */
    int flag = type & INTF_SOCK_NONBLOCK;
    type &= ~INTF_SOCK_NONBLOCK;

    socket = lwip_socket(domain, type, protocol);
    // sock_wqueue_add((void*)get_socket(socket));

    /* handle the socket options */
    if (socket >= 0 && flag != 0)
        unet_fcntl(socket, F_SETFL, flag);

    return socket;
}

int unet_close(int socket)
{
    int result = lwip_close(socket);
    // sock_wqueue_delete((void*)get_socket(socket));

    return result;
}

int unet_bind(int socket, const struct sockaddr *name, socklen_t namelen)
{
    return lwip_bind(socket, name, namelen);
}

int unet_listen(int socket, int backlog)
{
    return lwip_listen(socket, backlog);
}

int unet_connect(int socket, const struct sockaddr *name, socklen_t namelen)
{
    return lwip_connect(socket, name, namelen);
}

int unet_accept(int socket, struct sockaddr *addr, socklen_t *addrlen)
{
    socket = lwip_accept(socket, addr, addrlen);
    // sock_wqueue_add((void*)get_socket(socket));

    return socket;
}

int unet_sendto(int socket, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen)
{
    int result;
    if(tolen  == 0)
    {
        result = lwip_sendto(socket, data, size, flags, RT_NULL, RT_NULL);
    }
    else
    {
        result = lwip_sendto(socket, data, size, flags, to, tolen);
    }
    if(result <= 0)
    {
        rt_kprintf("%s line %d sendto error\n",__func__,__LINE__);
    }
    return result;
}

int unet_recvfrom(int socket, void *mem, size_t size, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    if(from && fromlen)
    {
        return lwip_recvfrom(socket, mem, size, flags, from, fromlen);
    }
    else
    {
        return lwip_recvfrom(socket, mem, size, flags, RT_NULL, RT_NULL);
    }
}

int unet_getsockopt(int socket, int level, int optname, void *optval, socklen_t *optlen)
{
    return lwip_getsockopt(socket, level, optname, optval, optlen);
}

int unet_setsockopt(int socket, int level, int optname, const void *optval, socklen_t optlen)
{
    return lwip_setsockopt(socket, level, optname, optval, optlen);
}

int unet_shutdown(int socket, int how)
{
    return lwip_shutdown(socket, how);
}

int unet_getpeername(int socket, struct sockaddr *name, socklen_t *namelen)
{
    return lwip_getpeername(socket, name, namelen);
}

int unet_getsockname(int socket, struct sockaddr *name, socklen_t *namelen)
{
    return lwip_getsockname(socket, name, namelen);
}

int unet_fcntl(int socket, int cmd, int val)
{
    return lwip_fcntl(socket, cmd, val);
}

/* Observe the 'real' IOCTL operations in unet 'api/sockets.c' and find that
 * 'argp' is used as an integer pointer. */
int unet_ioctl(int socket, long cmd, void *argp)
{
    return lwip_ioctl(socket, cmd, argp);
}
#include <stdio.h>
struct hostent* unet_gethostbyname(const char *name)
{
    static struct hostent s_hostent, *p_hostent = RT_NULL;
    static char *s_aliases;
    static ip_addr_t s_hostent_addr;
    static ip_addr_t *s_phostent_addr[2];
    static char s_hostname[DNS_MAX_NAME_LENGTH + 1];
    p_hostent = lwip_gethostbyname(name);
    memset(&s_hostent, 0, sizeof(s_hostent));
    /* fill hostent */
    s_hostent_addr = *((ip_addr_t *) p_hostent->h_addr);
    s_phostent_addr[0] = &s_hostent_addr;
    s_phostent_addr[1] = NULL;
    strncpy(s_hostname, name, DNS_MAX_NAME_LENGTH);
    s_hostname[DNS_MAX_NAME_LENGTH] = 0;
    s_hostent.h_name = s_hostname;
    s_aliases = NULL;
    s_hostent.h_aliases = &s_aliases;
    s_hostent.h_addrtype = AF_INET;
    s_hostent.h_length = sizeof(ip_addr_t);
    s_hostent.h_addr_list = (char**)&s_phostent_addr;
    p_hostent = &s_hostent;

    return p_hostent;
}

int unet_gethostbyname_r(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
    return 0;
}

int unet_getaddrinfo(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res)
{
    return lwip_getaddrinfo(nodename, servname, hints, res);
}

void unet_freeaddrinfo(struct addrinfo *ai)
{
    lwip_freeaddrinfo(ai);
}

