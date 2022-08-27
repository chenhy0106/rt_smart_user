/*
 * Copyright (c) 2011-2020, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-12     quanzhao     the first version
 */
#include <rtthread.h>
#include <lwp.h>
#include <lwp_shm.h>

#include <sal_socket.h>
#include <sal_netdb.h>      /* struct hostent */

#include "unet.h"

#define K_AI_ADDR_OFFSET (16)
rt_uint8_t k_ai_addr[K_AI_ADDR_OFFSET];
/*
 * For each command to transfer, we allocate a shared memory region and put in
 * the command structure and the possible extra data following it.
 */
static size_t key = 1;
int compose_cmd(uint32_t cmd, void *arg0, void *arg1, void *arg2,
        void *arg3, void *arg4, void *arg5, size_t datalen)
{
    int shmid;
    void *shm_vaddr;

    /* the shared memory includes the command and the possible data */
    size_t len = datalen + UNET_CMD_OFFSET;

    /*
     * Usually use the current thread ID to label the shared memory, like this:
     * size_t key = (size_t) rt_thread_self();
     *
     * But we need to send commands to 2 channels, here is a simple way to avoid
     * ID conflicts.
     */
    // size_t key = (size_t) rt_thread_self();
    key = key + 2;
    
    shmid = lwp_shmget(key, len, 1);    /* create a new shared-memory */
    if (shmid == -1)
    {
        rt_kprintf("Fail to allocate a shared memory, len = %d!\n", len);
        return -1;
    }

    /* get the start address of the shared memory */
    shm_vaddr = lwp_shminfo(shmid);
    if (shm_vaddr == RT_NULL)
    {
        rt_kprintf("The allocated shared memory doesn't have a valid address!\n");
        return -1;
    }

    /* prepare the command structure */
    struct unet_cmd *pcmd = (struct unet_cmd *) shm_vaddr;
    pcmd->cmd = cmd;
    pcmd->argv[0] = arg0;
    pcmd->argv[1] = arg1;
    pcmd->argv[2] = arg2;
    pcmd->argv[3] = arg3;
    pcmd->argv[4] = arg4;
    pcmd->argv[5] = arg5;

    return shmid;
}

/*
 * The following functions implement the system calls propogated downwards from
 * SAL. They simply prepare the corresponding commands and send them to unet in
 * user mode and return the result back to SAL.
 */
/*
 * In the network stack implementation, the argument 'type' must NOT include any
 * socket options. To solve the issue, we do it separately in 2 steps.
 */
#define INTF_SOCK_NONBLOCK  SOCK_NONBLOCK
#define IMPL_SOCK_NONBLOCK  1
int unet_socket(int domain, int type, int protocol)
{
    int shmid;
    int socket;
    struct unet_cmd *unet_cmd;

    /* filter-out socket options: SOCK_NONBLOCK & SOCK_CLOEXEC (not supported) */
    int flag = type & INTF_SOCK_NONBLOCK;
    type &= ~INTF_SOCK_NONBLOCK;

    shmid = compose_cmd3(UNET_SRV_CMD_SOCKET, (void *)(size_t)domain, (void *)(size_t)type, (void *)(size_t)protocol, 0);
    if (shmid < 0)
    {
        rt_kprintf("%s get shmid %d failed\n",__func__,shmid);
        return -1;
    }
        
    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    socket = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    sock_wqueue_add(unet_cmd->argv[0]);

    lwp_shmrm(shmid);

    /* handle the socket options */
    if (socket >= 0 && flag != 0)
        unet_fcntl(socket, F_SETFL, flag);

    return socket;
}

int unet_close(int socket)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;

    shmid = compose_cmd1(UNET_SRV_CMD_CLOSE, (void *)(size_t)socket, 0);
    if (shmid < 0)
        return -1;

    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    sock_wqueue_delete(unet_cmd->argv[0]);

    lwp_shmrm(shmid);

    return result;
}

int unet_bind(int socket, const struct sockaddr *name, socklen_t namelen)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;

    shmid = compose_cmd3(UNET_SRV_CMD_BIND, (void *)(size_t)socket, RT_NULL, (void *)(size_t)namelen, namelen);
    if (shmid < 0)
        return -1;

    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    rt_memcpy((void *)unet_cmd + UNET_CMD_OFFSET, name, namelen);

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);
    lwp_shmrm(shmid);

    return result;
}

int unet_listen(int socket, int backlog)
{
    int shmid, result;

    shmid = compose_cmd2(UNET_SRV_CMD_LISTEN, (void *)(size_t)socket, (void *)(size_t)backlog, 0);
    if (shmid < 0)
        return -1;

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);
    lwp_shmrm(shmid);

    return result;
}

int unet_connect(int socket, const struct sockaddr *name, socklen_t namelen)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;
    shmid = compose_cmd3(UNET_SRV_CMD_CONNECT, (void *)(size_t)socket, RT_NULL, (void *)(size_t)namelen, namelen);
    if (shmid < 0)
        return -1;

    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    rt_memcpy((void *)unet_cmd + UNET_CMD_OFFSET, name, namelen);

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);
    lwp_shmrm(shmid);
    return result;
}

int unet_accept(int socket, struct sockaddr *addr, socklen_t *addrlen)
{
    int shmid;
    struct unet_cmd *unet_cmd;

    shmid = compose_cmd3(UNET_SRV_CMD_ACCEPT, (void *)(size_t)socket,
            (void *)(size_t)UNET_CMD_OFFSET, (void *)(size_t)*addrlen, UNET_RECV_DATA_MAXLEN);
    if (shmid < 0)
        return -1;
    socket = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    /* copy the returned information to the locations specified by arguments */
    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    *addrlen = (socklen_t)(size_t)unet_cmd->argv[2];
    rt_memcpy(addr, (void *)(size_t)unet_cmd + (int)(size_t)unet_cmd->argv[1], *addrlen);
    sock_wqueue_add(unet_cmd->argv[0]);

    lwp_shmrm(shmid);
    return socket;
}

int unet_sendto(int socket, const void *data, size_t size, int flags, const struct sockaddr *to, socklen_t tolen)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;
    void *shm_data, *shm_to;

    size_t len = size + tolen;

    shmid = compose_cmd(UNET_SRV_CMD_SENDTO, (void *)(size_t)socket, RT_NULL,
            (void *)size, (void *)(size_t)flags, RT_NULL, (void *)(size_t)tolen, len);
    if (shmid < 0)
        return -1;

    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);

    /* prepare the sending address */
    shm_to = (void *)unet_cmd + UNET_CMD_OFFSET;
    rt_memcpy(shm_to, to, tolen);
    unet_cmd->argv[4] = (void *)(size_t)UNET_CMD_OFFSET;  /* offset */

    /* prepare the sending data */
    shm_data = (void *)unet_cmd + UNET_CMD_OFFSET + tolen;
    rt_memcpy(shm_data, data, size);
    unet_cmd->argv[1] = (void *)(size_t)UNET_CMD_OFFSET + tolen;

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    lwp_shmrm(shmid);
    return result;
}

int unet_recvfrom(int socket, void *mem, size_t size, int flags, struct sockaddr *from, socklen_t *fromlen)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;
    void *shm_mem, *shm_from;
    int loops = 0;
    size_t len = size + sizeof(struct sockaddr);

    while (1)
    {
        if(from && fromlen)
        {
            shmid = compose_cmd(UNET_SRV_CMD_RECVFROM, (void *)(size_t)socket, RT_NULL,
                (void *)size, (void *)(size_t)flags, RT_NULL, (void *)(size_t)*fromlen, len);
        }

        else
        {
            shmid = compose_cmd(UNET_SRV_CMD_RECVFROM, (void *)(size_t)socket, RT_NULL,
                (void *)size, (void *)(size_t)flags, RT_NULL, RT_NULL, len);
        }

        if (shmid < 0)
            return -1;

        unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);

        /* prepare the sending address */
        shm_from = (void *)unet_cmd + UNET_CMD_OFFSET;
        unet_cmd->argv[4] = (void *)(size_t)UNET_CMD_OFFSET;      /* offset */

        /* prepare the sending data */
        shm_mem = (void *)unet_cmd + UNET_CMD_OFFSET + sizeof(struct sockaddr);
        unet_cmd->argv[1] = (void *)(size_t)UNET_CMD_OFFSET + sizeof(struct sockaddr);

        result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);
        /* data might arrive later and it's worthy to give it a second try */
        if (result != -2)
            break;
        /* The blocking-read thread was waken up once before, but there are
         * still no date to fetch, we assume the time is over. */
        if (loops)
        {
            lwp_shmrm(shmid);
            return -1;
        }
        sock_wqueue_suspend(unet_cmd->argv[0], (uint32_t)(size_t)unet_cmd->argv[1]);
        lwp_shmrm(shmid);
        loops++;
    }
    rt_memcpy(mem, shm_mem, size);
    /* copy the result data back */
    if (from && fromlen)
    {
        *fromlen = (socklen_t)(size_t)unet_cmd->argv[5];
        rt_memcpy(from, shm_from, *fromlen);
    }

    lwp_shmrm(shmid);
    return result;
}

int unet_getsockopt(int socket, int level, int optname, void *optval, socklen_t *optlen)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;

    shmid = compose_cmd5(UNET_SRV_CMD_GETSOCKOPT, (void *)(size_t)socket, (void *)(size_t)level,
            (void *)(size_t)optname, (void *)(size_t)UNET_CMD_OFFSET, (void *)(size_t)*optlen, UNET_RECV_DATA_MAXLEN);
    if (shmid < 0)
        return -1;

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    *optlen = (socklen_t)(size_t)unet_cmd->argv[4];
    rt_memcpy(optval, (void *)unet_cmd + (int)(size_t)unet_cmd->argv[3], *optlen);

    lwp_shmrm(shmid);
    return result;
}

int unet_setsockopt(int socket, int level, int optname, const void *optval, socklen_t optlen)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;

    shmid = compose_cmd5(UNET_SRV_CMD_SETSOCKOPT, (void *)(size_t)socket, (void *)(size_t)level,
            (void *)(size_t)optname, (void *)(size_t)UNET_CMD_OFFSET, (void *)(size_t)optlen, optlen);
    if (shmid < 0)
        return -1;

    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    void *shm_optval = (void *)unet_cmd + (int)(size_t)unet_cmd->argv[3];
    rt_memcpy(shm_optval, optval, optlen);

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    lwp_shmrm(shmid);
    return result;
}

int unet_shutdown(int socket, int how)
{
    int shmid, result;

    shmid = compose_cmd2(UNET_SRV_CMD_SHUTDOWN, (void *)(size_t)socket, (void *)(size_t)how, 0);
    if (shmid < 0)
        return -1;

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    lwp_shmrm(shmid);
    return result;
}

int unet_getpeername(int socket, struct sockaddr *name, socklen_t *namelen)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;

    shmid = compose_cmd3(UNET_SRV_CMD_GETPEERNAME, (void *)(size_t)socket,
            (void *)(size_t)UNET_CMD_OFFSET, (void *)(size_t)*namelen, UNET_RECV_DATA_MAXLEN);
    if (shmid < 0)
        return -1;

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    *namelen = (socklen_t)(size_t)unet_cmd->argv[2];
    rt_memcpy(name, (void *)unet_cmd + (int)(size_t)unet_cmd->argv[1], *namelen);

    lwp_shmrm(shmid);
    return result;
}

int unet_getsockname(int socket, struct sockaddr *name, socklen_t *namelen)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;

    shmid = compose_cmd3(UNET_SRV_CMD_GETSOCKNAME, (void *)(size_t)socket,
            (void *)(size_t)UNET_CMD_OFFSET, (void *)(size_t)*namelen, UNET_RECV_DATA_MAXLEN);
    if (shmid < 0)
        return -1;

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    *namelen = (socklen_t)(size_t)unet_cmd->argv[2];
    rt_memcpy(name, (void *)unet_cmd + (int)(size_t)unet_cmd->argv[1], *namelen);

    lwp_shmrm(shmid);
    return result;
}

int unet_fcntl(int socket, int cmd, int val)
{
    int shmid, result;

    shmid = compose_cmd3(UNET_SRV_CMD_FCNTL, (void *)(size_t)socket, (void *)(size_t)cmd, (void *)(size_t)val, 0);
    if (shmid < 0)
        return -1;

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    lwp_shmrm(shmid);
    return result;
}

/* Observe the 'real' IOCTL operations in unet 'api/sockets.c' and find that
 * 'argp' is used as an integer pointer. */
int unet_ioctl(int socket, long cmd, void *argp)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;

    shmid = compose_cmd3(UNET_SRV_CMD_IOCTL, (void *)(size_t)socket, (void *)(size_t)cmd, RT_NULL, 0);
    if (shmid < 0)
        return -1;

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);
    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    *(int *)argp = (socklen_t)(size_t)unet_cmd->argv[2];

    lwp_shmrm(shmid);
    return result;
}

struct hostent* unet_gethostbyname(const char *name)
{
    static struct hostent s_hostent, *p_hostent = RT_NULL;
    static char *s_aliases;
    static ip_addr_t s_hostent_addr;
    static ip_addr_t *s_phostent_addr[2];
    static char s_hostname[DNS_MAX_NAME_LENGTH + 1];

    /* query host IP address */
    int shmid;
    struct unet_cmd *unet_cmd;
    shmid = compose_cmd1(UNET_SRV_CMD_GETHOSTBYNAME, (void *)(size_t)UNET_CMD_OFFSET,
            DNS_MAX_NAME_LENGTH + 1);
    if (shmid < 0)
        return NULL;

    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    char *arg_name = (char *)unet_cmd + UNET_CMD_OFFSET;
    rt_memcpy(arg_name, name, DNS_MAX_NAME_LENGTH);
    arg_name[DNS_MAX_NAME_LENGTH-1] = 0;

    memset(&s_hostent, 0, sizeof(s_hostent));
    p_hostent = RT_NULL;
    if (unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid))
    {
        /* fill hostent */
        s_hostent_addr = *((ip_addr_t *) &unet_cmd->argv[0]);
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
    }

    lwp_shmrm(shmid);
    return p_hostent;
}

int unet_gethostbyname_r(const char *name, struct hostent *ret, char *buf, size_t buflen, struct hostent **result, int *h_errnop)
{
    return 0;
}

/* The functions 'unet_getaddrinfo()/unet_freeaddrinfo()' in unet allocate and
 * free a 'addrinfo' structure, which could not be accessed directly in kernel.
 * Thus, we have to allocate and free another 'addrinfo' structure in kernel
 * synchronously to store the corresponding data and record the pointer to the
 * one in the user mode at the same time. */
struct k_addrinfo {
    struct addrinfo real_ai;    /* the data of 'addrinfo' */
    struct addrinfo *u_ai;      /* the pointer in user mode */
};

int unet_getaddrinfo(const char *nodename, const char *servname, const struct addrinfo *hints, struct addrinfo **res)
{
    int shmid, result;
    struct unet_cmd *unet_cmd;

    /* We transfer 3 arguments into the user mode and get 1 structure 'addrinfo'
     * back to the kernel. All of the data are stored in the shared-memory
     * temporarily, thus the alignment issue should be concerned. */
#define ALIGN_STRING(s) (((strlen(s) + 1)/sizeof(struct addrinfo) + 1) * sizeof(struct addrinfo))
    int aligned_len_nodename = ALIGN_STRING(nodename);
    int aligned_len_servname;
    if(servname != NULL)
    {
        aligned_len_servname = ALIGN_STRING(servname);
    }
    else
    {
        aligned_len_servname = 1;
    }
#undef ALIGN_STRING

    /* the offsets of the data stored in the shared-memory */
    int offset_nodename = (UNET_CMD_OFFSET/sizeof(struct addrinfo) + 1) * sizeof(struct addrinfo);
    int offset_servname = offset_nodename + aligned_len_nodename;
    int offset_hints    = offset_servname + aligned_len_servname;
    int offset_res      = offset_hints + sizeof(struct addrinfo);
    int offset_addr     = offset_res + sizeof(struct sockaddr);
    int total_len       = offset_addr + sizeof(struct addrinfo);
    /* Here it is a bit complicated. We put the offsets for each arguments in
     * the shared-memory in 'unet_cmd->argv[]', including the 4th one. However,
     * when it returns, the pointer to the allocated 'addrinfo' in the user mode
     * is stored in 'unet_cmd->argv[3]'. */
    shmid = compose_cmd5(UNET_SRV_CMD_GETADDRINFO, (void *)(size_t)offset_nodename,
            (void *)(size_t)offset_servname, (void *)(size_t)offset_hints, (void *)(size_t)offset_res,(void *)(size_t)offset_addr,
            total_len);
    if (shmid < 0)
        return -1;

    /* fill the shared-memory with the data needed by the first 3 arguments */
    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    rt_memcpy((void *)unet_cmd + offset_nodename, nodename, strlen(nodename)+1);
    if(servname != NULL)
    {
        rt_memcpy((void *)unet_cmd + offset_servname, servname, strlen(servname)+1);
    }
    else
    {
        int servname_null_flag = 0;
        rt_memcpy((void *)unet_cmd + offset_servname, &servname_null_flag, 1);
    }
    rt_memcpy((void *)unet_cmd + offset_hints, hints, sizeof(struct addrinfo));

    /* Before requesting to allocate a 'addrinfo' in the user mode, we try to
     * allocate one of the kernel version first. */
    struct k_addrinfo *k_ai = rt_malloc(sizeof(struct k_addrinfo));
    if (k_ai == RT_NULL)
    {
        rt_kprintf("Fail to allocate a structure \'addrinfo\' for \'unet_getaddrinfo()\' in kernel.\n");
        lwp_shmrm(shmid);
        return -1;
    }

    result = (int)(size_t)unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);

    if (result == 0)
    {
        /* copy the returned 'addrinfo' and the pointer in user mode */
        rt_memcpy(&k_ai->real_ai, (void *)unet_cmd + offset_res, sizeof(struct addrinfo));
        rt_memcpy(k_ai_addr, (void *)unet_cmd +  offset_res + sizeof(struct sockaddr), sizeof(struct sockaddr));
        k_ai->u_ai = unet_cmd->argv[3];    /* the pointer in user mode */

        k_ai->real_ai.ai_addr = (struct sockaddr *)k_ai_addr;
        /* return the structure in kernel */
        *res = (struct addrinfo *)k_ai;
    }

    lwp_shmrm(shmid);
    return result;
}

void unet_freeaddrinfo(struct addrinfo *ai)
{
    struct k_addrinfo *k_ai = (struct k_addrinfo *)ai;
    int shmid = compose_cmd1(UNET_SRV_CMD_FREEADDRINFO, k_ai->u_ai, 0);

    unet_cmd_send_recv(unet_get_stack_channel(), (void *)(size_t)shmid);
    rt_free(k_ai);

    lwp_shmrm(shmid);
}

