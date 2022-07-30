#ifndef CHANNEL_H__
#define CHANNEL_H__

#include <rtthread.h>
#include <lwp_shm.h>
#include <stdio.h>

rt_inline void *channel_cmd_send_recv(int channel, void *cmd)
{
    RT_ASSERT(channel >= 0);

    /* wrap the command and data into an IPC message */
    struct rt_channel_msg chn_msg;
    chn_msg.type   = RT_CHANNEL_RAW;
    chn_msg.u.d    = cmd;

    /* send the command and wait for the result */
    rt_channel_send_recv(channel, &chn_msg, &chn_msg);

    /* Watch this, we use a void pointer to transfer the returned value. */
    return chn_msg.u.d;
}

rt_inline void channel_cmd_send(int channel, void *cmd)
{
    RT_ASSERT(channel >= 0);

    /* wrap the command and data into an IPC message */
    struct rt_channel_msg chn_msg;
    chn_msg.type   = RT_CHANNEL_RAW;
    chn_msg.u.d    = cmd;

    /* send the command and not wait for the result */
    rt_channel_send(channel, &chn_msg);
}

rt_inline void *channel_cmd_recv(int channel)
{
    RT_ASSERT(channel >= 0);

    struct rt_channel_msg chn_msg;
    chn_msg.type = RT_CHANNEL_RAW;
    rt_channel_recv(channel, &chn_msg);

    return chn_msg.u.d;
}

rt_inline void channel_cmd_reply(int channel, void *cmd)
{
    RT_ASSERT(channel >= 0);

    struct rt_channel_msg chn_msg;
    chn_msg.type = RT_CHANNEL_RAW;
    chn_msg.u.d = cmd;

    rt_channel_reply(channel, &chn_msg);
}

#define CHANNEL_CMD_MAX_ARGS   6   /* maximum number of arguments in channel */
struct channel_cmd
{
    uint32_t cmd;
    void *argv[CHANNEL_CMD_MAX_ARGS];
};

/* When shared-memory is used to transfer the command and data at the same time,
 * the command is put at the begining while the data follows at the offset
 * 'CHANNEL_CMD_OFFSET'. */
#define CHANNEL_CMD_OFFSET    sizeof(struct channel_cmd)
#define CHANNEL_CMD_DATA(cmd) ((void *)((cmd) + 1))

/* In microkernel, shared-memory is used to transfer received data in pages. For
 * now, we limite the total size of command and data to one page. */
#define CHANNEL_RECV_DATA_MAXLEN    (4096-CHANNEL_CMD_OFFSET)

/* conventional wrappers */
#define channel_compose_cmd0(c, l)                          \
    channel_compose_cmd(c, NULL, NULL, NULL, NULL, NULL, NULL, l)
#define channel_compose_cmd1(c, a0, l)                      \
    channel_compose_cmd(c, a0, NULL, NULL, NULL, NULL, NULL, l)
#define channel_compose_cmd2(c, a0, a1, l)                  \
    channel_compose_cmd(c, a0, a1, NULL, NULL, NULL, NULL, l)
#define channel_compose_cmd3(c, a0, a1, a2, l)              \
    channel_compose_cmd(c, a0, a1, a2, NULL, NULL, NULL, l)
#define channel_compose_cmd4(c, a0, a1, a2, a3, l)          \
    channel_compose_cmd(c, a0, a1, a2, a3, NULL, NULL, l)
#define channel_compose_cmd5(c, a0, a1, a2, a3, a4, l)      \
    channel_compose_cmd(c, a0, a1, a2, a3, a4, NULL, l)
#define channel_compose_cmd6(c, a0, a1, a2, a3, a4, a5, l)  \
    channel_compose_cmd(c, a0, a1, a2, a3, a4, a5, l)

int channel_compose_cmd(uint32_t cmd, void *arg0, void *arg1, void *arg2,
    void *arg3, void *arg4, void *arg5, size_t datalen);

#endif

