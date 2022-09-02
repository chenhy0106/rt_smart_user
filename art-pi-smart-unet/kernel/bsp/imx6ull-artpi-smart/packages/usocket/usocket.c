#include "usocket.h"
#include <unet.h>
#include <lwp_user_mm.h>

/* The same socket option is defined differently in the user interfaces and the
 * implementation. The options should be converted in the kernel. */

/* socket levels */
#define INTF_SOL_SOCKET     1
#define IMPL_SOL_SOCKET     0xFFF

#define INTF_IPPROTO_IP     0
#define IMPL_IPPROTO_IP     0

#define INTF_IPPROTO_TCP    6
#define IMPL_IPPROTO_TCP    6

#define INTF_IPPROTO_IPV6   41
#define IMPL_IPPROTO_IPV6   41

/* SOL_SOCKET option names */
#define INTF_SO_BROADCAST   6
#define INTF_SO_KEEPALIVE   9
#define INTF_SO_REUSEADDR   2
#define INTF_SO_TYPE        3
#define INTF_SO_ERROR       4
#define INTF_SO_SNDTIMEO    21
#define INTF_SO_RCVTIMEO    20
#define INTF_SO_RCVBUF      8
#define INTF_SO_LINGER      13
#define INTF_SO_NO_CHECK    11
#define INTF_SO_ACCEPTCONN  30
#define INTF_SO_DONTROUTE   5
#define INTF_SO_OOBINLINE   10
#define INTF_SO_REUSEPORT   15
#define INTF_SO_SNDBUF      7
#define INTF_SO_SNDLOWAT    19
#define INTF_SO_RCVLOWAT    18

#define IMPL_SO_BROADCAST   0x0020
#define IMPL_SO_KEEPALIVE   0x0008
#define IMPL_SO_REUSEADDR   0x0004
#define IMPL_SO_TYPE        0x1008
#define IMPL_SO_ERROR       0x1007
#define IMPL_SO_SNDTIMEO    0x1005
#define IMPL_SO_RCVTIMEO    0x1006
#define IMPL_SO_RCVBUF      0x1002
#define IMPL_SO_LINGER      0x0080
#define IMPL_SO_NO_CHECK    0x100a
#define IMPL_SO_ACCEPTCONN  0x0002
#define IMPL_SO_DONTROUTE   0x0010
#define IMPL_SO_OOBINLINE   0x0100
#define IMPL_SO_REUSEPORT   0x0200
#define IMPL_SO_SNDBUF      0x1001
#define IMPL_SO_SNDLOWAT    0x1003
#define IMPL_SO_RCVLOWAT    0x1004

/* IPPROTO_IP option names */
#define INTF_IP_TTL 2
#define INTF_IP_TOS 1
#define INTF_IP_MULTICAST_TTL   33
#define INTF_IP_MULTICAST_IF    32
#define INTF_IP_MULTICAST_LOOP  34
#define INTF_IP_ADD_MEMBERSHIP  35
#define INTF_IP_DROP_MEMBERSHIP 36

#define IMPL_IP_TTL  2
#define IMPL_IP_TOS  1
#define IMPL_IP_MULTICAST_TTL   5
#define IMPL_IP_MULTICAST_IF    6
#define IMPL_IP_MULTICAST_LOOP  7
#define IMPL_IP_ADD_MEMBERSHIP  3
#define IMPL_IP_DROP_MEMBERSHIP 4

/* IPPROTO_TCP option names */
#define INTF_TCP_NODELAY    1
#define INTF_TCP_KEEPALIVE  9
#define INTF_TCP_KEEPIDLE   4
#define INTF_TCP_KEEPINTVL  5
#define INTF_TCP_KEEPCNT    6

#define IMPL_TCP_NODELAY    0x01
#define IMPL_TCP_KEEPALIVE  0x02
#define IMPL_TCP_KEEPIDLE   0x03
#define IMPL_TCP_KEEPINTVL  0x04
#define IMPL_TCP_KEEPCNT    0x05

/* IPPROTO_IPV6 option names */
#define INTF_IPV6_V6ONLY    26
#define IMPL_IPV6_V6ONLY    27

static void convert_sockopt(int *level, int *optname)
{
    if (*level == INTF_SOL_SOCKET)
    {
        *level = IMPL_SOL_SOCKET;

        switch (*optname)
        {
            case INTF_SO_REUSEADDR:
                *optname = IMPL_SO_REUSEADDR;
                break;
            case INTF_SO_KEEPALIVE:
                *optname = IMPL_SO_KEEPALIVE;
                break;
            case INTF_SO_BROADCAST:
                *optname = IMPL_SO_BROADCAST;
                break;
            case INTF_SO_ACCEPTCONN:
                *optname = IMPL_SO_ACCEPTCONN;
                break;
            case INTF_SO_DONTROUTE:
                *optname = IMPL_SO_DONTROUTE;
                break;
            case INTF_SO_LINGER:
                *optname = IMPL_SO_LINGER;
                break;
            case INTF_SO_OOBINLINE:
                *optname = IMPL_SO_OOBINLINE;
                break;
            case INTF_SO_REUSEPORT:
                *optname = IMPL_SO_REUSEPORT;
                break;
            case INTF_SO_SNDBUF:
                *optname = IMPL_SO_SNDBUF;
                break;
            case INTF_SO_RCVBUF:
                *optname = IMPL_SO_RCVBUF;
                break;
            case INTF_SO_SNDLOWAT:
                *optname = IMPL_SO_SNDLOWAT;
                break;
            case INTF_SO_RCVLOWAT:
                *optname = IMPL_SO_RCVLOWAT;
                break;
            case INTF_SO_SNDTIMEO:
                *optname = IMPL_SO_SNDTIMEO;
                break;
            case INTF_SO_RCVTIMEO:
                *optname = IMPL_SO_RCVTIMEO;
                break;
            case INTF_SO_ERROR:
                *optname = IMPL_SO_ERROR;
                break;
            case INTF_SO_TYPE:
                *optname = IMPL_SO_TYPE;
                break;
            case INTF_SO_NO_CHECK:
                *optname = IMPL_SO_NO_CHECK;
                break;

            /*
             * SO_DONTLINGER (*level = ((int)(~SO_LINGER))),
             * SO_USELOOPBACK (*level = 0x0040) and
             * SO_CONTIMEO (*level = 0x1009) are not supported for now.
             */
            default:
                *optname = 0;
                break;
        }
        return;
    }

    if (*level == INTF_IPPROTO_IP)
    {
        *level = IMPL_IPPROTO_IP;

        switch (*optname)
        {
            case INTF_IP_TTL:
                *optname = IMPL_IP_TTL;
                break;
            case INTF_IP_TOS:
                *optname = IMPL_IP_TOS;
                break;
            case INTF_IP_MULTICAST_TTL:
                *optname = IMPL_IP_MULTICAST_TTL;
                break;
            case INTF_IP_MULTICAST_IF:
                *optname = IMPL_IP_MULTICAST_IF;
                break;
            case INTF_IP_MULTICAST_LOOP:
                *optname = IMPL_IP_MULTICAST_LOOP;
                break;
            case INTF_IP_ADD_MEMBERSHIP:
                *optname = IMPL_IP_ADD_MEMBERSHIP;
                break;
            case INTF_IP_DROP_MEMBERSHIP:
                *optname = IMPL_IP_DROP_MEMBERSHIP;
                break;
            default:
                break;
        }
    }

    if (*level == INTF_IPPROTO_TCP)
    {
        *level = IMPL_IPPROTO_TCP;

        switch (*optname)
        {
            case INTF_TCP_NODELAY:
                *optname = IMPL_TCP_NODELAY;
                break;
            case INTF_TCP_KEEPALIVE:
                *optname = IMPL_TCP_KEEPALIVE;
                break;
            case INTF_TCP_KEEPIDLE:
                *optname = IMPL_TCP_KEEPIDLE;
                break;
            case INTF_TCP_KEEPINTVL:
                *optname = IMPL_TCP_KEEPINTVL;
                break;
            case INTF_TCP_KEEPCNT:
                *optname = IMPL_TCP_KEEPCNT;
                break;
            default:
                break;
        }
        return;
    }

    if (*level == INTF_IPPROTO_IPV6)
    {
        *level = IMPL_IPPROTO_IPV6;

        switch (*optname)
        {
            case INTF_IPV6_V6ONLY:
                *optname = IMPL_IPV6_V6ONLY;
                break;
            default:
                break;
        }
        return;
    }

}

static int recv_shmid = -1;
static int usocket_channel = -1;
const char * usocket_name = "lwIPKit";

#define STATIC_SHM_SIZE (2 * 4096 - UNET_CMD_OFFSET)
// #define STATIC_SHM_SIZE UNET_RECV_DATA_MAXLEN

int u_socket_init()
{
    recv_shmid = compose_cmd0(UNET_SRV_CMD_RECVFROM, STATIC_SHM_SIZE);

    usocket_channel  = rt_channel_open(usocket_name, O_RDWR);
    if (usocket_channel < 0) 
    {
        usocket_channel = -1;
        rt_kprintf("u_socket_init fail\n");
        return -1;
    }
    else
    {
        return 0;
    }
}
// INIT_APP_EXPORT(u_socket_init);

int u_socket (int domain, int type, int protocol)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }

    int fd = -1;
    int nonblock = 0;
    /* not support SOCK_CLOEXEC type */
    if (type & SOCK_CLOEXEC)
    {
        type &= ~SOCK_CLOEXEC;
    }
    if (type & SOCK_NONBLOCK)
    {
        nonblock = 1;
        type &= ~SOCK_NONBLOCK;
    }

    // ipc fd = socket(domain, type, protocol);
    int shmid = compose_cmd3(UNET_SRV_CMD_SOCKET, (void*)domain, (void*)type, (void*)protocol, 0);
    struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    if (cmd)
    {
        fd = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
        lwp_shmdt(cmd);
        lwp_shmrm(shmid);
    }

    if (fd < 0)
    {
        goto out;
    }
    if (nonblock)
    {
        fcntl(fd, F_SETFL, O_NONBLOCK);
    }

out:
    return fd;
}

int u_bind (int socket, const struct sockaddr *name, socklen_t namelen)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }
    // if (!lwp_user_accessable((void *)name, namelen))
    // {
    //     return -EFAULT;
    // }
    #ifdef SAL_USING_AF_UNIX
    if (name->sa_family  == AF_UNIX)
    {
        namelen = sizeof(struct sockaddr);
    }
    #endif /* SAL_USING_AF_UNIX */
    // return bind(socket, &sa, namelen);
    int res = -1;
    int shmid = compose_cmd2(UNET_SRV_CMD_BIND, (void*)socket, (void*)namelen, namelen);
    struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    if (cmd)
    {
        void *ptr = (void*)cmd + UNET_CMD_OFFSET;
        memcpy(ptr, name, namelen);
        res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
    return res;
}

int u_connect (int socket, const struct sockaddr *name, socklen_t namelen)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }
    // if (!lwp_user_accessable((void *)name, namelen))
    // {
    //     return -EFAULT;
    // }

    #ifdef SAL_USING_AF_UNIX
    if (name->sa_family  == AF_UNIX)
    {
        namelen = sizeof(struct sockaddr);
    }
    #endif /* SAL_USING_AF_UNIX */

    // return bind(socket, &sa, namelen);
    int res = -1;
    int shmid = compose_cmd2(UNET_SRV_CMD_CONNECT, (void*)socket, (void*)namelen, namelen);
    struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    if (cmd)
    {
        void *ptr = (void*)cmd + UNET_CMD_OFFSET;
        memcpy(ptr, name, namelen);
        res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
    return res;
}
int u_listen (int socket, int backlog)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }

    int res = -1;
    int shmid = compose_cmd2(UNET_SRV_CMD_LISTEN, (void*)socket, (void*)backlog, 0);
    struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    if (cmd)
    {
        res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
    return res;
}

int u_accept (int socket, struct sockaddr *addr, socklen_t *addrlen)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }

    // if (addr)
    // {
        // if (!lwp_user_accessable(addrlen, sizeof (socklen_t)))
        // {
        //     return -EFAULT;
        // }

        // if (!lwp_user_accessable(addr, *addrlen))
        // {
        //     return -EFAULT;
        // }
    // }

    int res = -1;
    int shmid = compose_cmd2(UNET_SRV_CMD_ACCEPT, (void*)socket, (void*)*addrlen, UNET_RECV_DATA_MAXLEN);
    struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    if (cmd)
    {
        res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
        if (res >= 0)
        {
            if (addr)
            {
                void *ptr = (void *)cmd + UNET_CMD_OFFSET;
                *addrlen = (socklen_t)(size_t)cmd->argv[1];
                memcpy(addr, ptr, *addrlen);
            }
        }
        
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
    return res;
}

ssize_t u_send (int socket, const void *dataptr, size_t size, int flags)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }

    int res = -1;
    int shmid = compose_cmd4(UNET_SRV_CMD_SENDTO, (void*)socket, (void*)size, (void*)flags, (void*)0, size);
    struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    if (cmd)
    {
        void *ptr = (void *)cmd + UNET_CMD_OFFSET;
        memcpy(ptr, dataptr, size);
        res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
    return res;
}

ssize_t u_recv (int socket, void *mem, size_t len, int flags)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }

    int shmid = recv_shmid;
    if (len > STATIC_SHM_SIZE)
    {
        shmid = compose_cmd4(UNET_SRV_CMD_RECVFROM, (void*)socket, (void*)len, (void*)flags, RT_NULL, len);
    }

    int res = -RT_ERROR;
    struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    cmd->argv[0] = (void*)socket;
    cmd->argv[1] = (void*)len;
    cmd->argv[2] = (void*)flags;

    if (cmd)
    {
        res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
        if (res >= 0)
        {
            void *ptr = (void*)cmd + UNET_CMD_OFFSET;
            memcpy(mem, ptr, len);
        }
        if (len > STATIC_SHM_SIZE)
        {
            lwp_shmdt(cmd);
        }
    }

    if (len > STATIC_SHM_SIZE)
    {
        lwp_shmrm(shmid);
    }
    return res;
}

ssize_t u_sendto (int socket, const void *dataptr, size_t size, int flags, const struct sockaddr *to, socklen_t tolen)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }
    
    if (!size)
    {
        return -EINVAL;
    }

    // if (!lwp_user_accessable((void *)dataptr, size))
    // {
    //     return -EFAULT;
    // }

    int res = -RT_ERROR;
    int shmid;

    if (to)
    {
        shmid = compose_cmd4(UNET_SRV_CMD_SENDTO, (void*)socket, (void*)size, (void*)flags, (void*)tolen, size+sizeof(struct sockaddr));
        struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
        if (cmd)
        {
            void *ptr = (void *)cmd + UNET_CMD_OFFSET;
            memcpy(ptr, dataptr, size);
            ptr += size;
            memcpy(ptr, to, sizeof(struct sockaddr));
            res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
            lwp_shmdt(cmd);
        }
    }
    else
    {
        shmid = compose_cmd4(UNET_SRV_CMD_SENDTO, (void*)socket, (void*)size, (void*)flags, (void*)0, size);
        struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
        if (cmd)
        {
            void *ptr = (void *)cmd + UNET_CMD_OFFSET;
            memcpy(ptr, dataptr, size);
            res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
            lwp_shmdt(cmd);
        }
    }

    lwp_shmrm(shmid);
    return res;
}

ssize_t u_recvfrom (int socket, void *mem, size_t len, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }
    
    if (!len)
    {
        return -EINVAL;
    }

    // if (!lwp_user_accessable((void *)mem, len))
    // {
    //     return -EFAULT;
    // }

    if (flags == 0x2)
    {
        flags = 0x1;
    }

    int res = -RT_ERROR;
    int shmid;

    if (from)
    {
        // ret = recvfrom(socket, kmem, len, flgs, &sa, fromlen);
        shmid = compose_cmd4(UNET_SRV_CMD_RECVFROM, (void*)socket, (void*)len, (void*)flags, (void*)*fromlen, len+sizeof(struct sockaddr));
        struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
        if (cmd)
        {
            res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
            *fromlen = (socklen_t)(size_t)cmd->argv[3];

            void *ptr = (void *)cmd + UNET_CMD_OFFSET;
            memcpy(mem, ptr, len);
            ptr += len;
            memcpy(from, ptr, sizeof(struct sockaddr));
            
            lwp_shmdt(cmd);
        }
    }
    else
    {
        shmid = compose_cmd4(UNET_SRV_CMD_RECVFROM, (void*)socket, (void*)len, (void*)flags, RT_NULL, len);
        struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
        if (cmd)
        {
            res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);
            if (res)
            {
                void *ptr = (void *)cmd + UNET_CMD_OFFSET;
                memcpy(mem, ptr, len);
            }
            lwp_shmdt(cmd);
        }
    }

    lwp_shmrm(shmid);
    return res;
}

int u_setsockopt (int socket, int level, int optname, const void *optval, socklen_t optlen)
{
    if (usocket_channel < 0)
    {
        u_socket_init();
        
    }
    
    int res = -RT_ERROR;;
    convert_sockopt(&level, &optname);

    int shmid = compose_cmd4(UNET_SRV_CMD_SETSOCKOPT, (void*)socket, (void*)level, (void*)optname, (void*)optlen, optlen);
    struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    if (cmd)
    {
        res = (int)unet_cmd_send_recv(usocket_channel, (void*)(size_t)shmid);

        void *ptr = (void *)cmd + UNET_CMD_OFFSET;
        memcpy(ptr, optval, optlen);
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
    return res;
}