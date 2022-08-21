#ifndef __UETH_ETH_H__
#define __UETH_ETH_H__

#include <rtthread.h>
#include <rtdef.h>
#include <ioremap.h>
#include <page.h>

#include <lwp.h>
#include <lwp_shm.h>

#include "../unet/unet.h"

#define CHANNEL_CMD_MAX_ARGS   6
struct channel_cmd
{
    uint32_t cmd;
    void *argv[CHANNEL_CMD_MAX_ARGS];
};
#define WORKLOAD_START sizeof(struct channel_cmd)

#define UETH_REMAP_REQ 1
#define UETH_GPIOINIT_REQ 2
#define UETH_CLOCKINIT_REQ 3
#define UETH_DCACHE_REQ 4
#define UETH_V2P_REQ 5
#define UETH_INSTALL_INTERRUPT_REQ 6
#define UETH_DEVICE_REGISTER 7
#define UETH_DEVICE_INIT 8
#define UNET_DEVICE_REGISTER        46
#define UNET_DEVICE_INIT            47

#define UETH_REMAP 1
#define UETH_UNMAP 2
#define UETH_REMAP_NOCACHE 3

#define UETH_DCACHE_CLEAN 1
#define UETH_DCACHE_INVALID 2

rt_inline void *ueth_cmd_send_recv(int channel, void *cmd, int interrupt)
{
    RT_ASSERT(channel >= 0);

    /* wrap the command and data into an IPC message */
    struct rt_channel_msg unet_msg;
    unet_msg.type   = RT_CHANNEL_RAW;
    unet_msg.u.d    = cmd;

    /* send the command and wait for the result */
    rt_channel_send_recv(channel, &unet_msg, &unet_msg);

    /* Watch this, we use a void pointer to transfer the returned value. */
    return unet_msg.u.d;
}

rt_inline void ueth_cmd_send(int channel, void *cmd, int interrupt)
{
    RT_ASSERT(channel >= 0);

    /* wrap the command and data into an IPC message */
    struct rt_channel_msg unet_msg;
    unet_msg.type   = RT_CHANNEL_RAW;
    unet_msg.u.d    = cmd;

    /* send the command and not wait for the result */
    if (interrupt)
    {
        rt_channel_send_interrupt(channel, &unet_msg);
    }
    else
    {
        rt_channel_send(channel, &unet_msg);
    }
}

rt_inline void *ueth_cmd_recv(int channel)
{
    RT_ASSERT(channel >= 0);

    struct rt_channel_msg unet_msg;
    unet_msg.type = RT_CHANNEL_RAW;
    rt_channel_recv(channel, &unet_msg);

    return unet_msg.u.d;
}

rt_inline void ueth_cmd_reply(int channel, void *cmd)
{
    RT_ASSERT(channel >= 0);

    struct rt_channel_msg unet_msg;
    unet_msg.type = RT_CHANNEL_RAW;
    unet_msg.u.d = cmd;
    rt_channel_reply(channel, &unet_msg);
}

#ifdef __cplusplus
extern "C" {
#endif

    int init_ueth_srv(void);

#ifdef __cplusplus
}
#endif

#endif

