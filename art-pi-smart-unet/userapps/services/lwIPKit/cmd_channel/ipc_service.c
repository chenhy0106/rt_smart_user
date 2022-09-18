#include "ipc_service.h"
#include <string.h>
#include <rtdef.h>
#define DBG_TAG "drv.enet"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <stdio.h>

static int ueth_ueth_srv_channel = -1;
const char *ueth_srv_name = "ipc_srv";
static int ueth_int_channel = -1;
const char *ueth_int_name = "ueth_int";

rt_err_t ipc_service_init()
{
    ueth_ueth_srv_channel = rt_channel_open(ueth_srv_name, O_RDWR);
    if (ueth_ueth_srv_channel < 0)
    {
        printf("open %s failed\n", ueth_srv_name);
        return RT_ERROR;
    }

    ueth_int_channel = rt_channel_open(ueth_int_name, O_RDWR);
    if (ueth_int_channel < 0)
    {
        printf("open %s failed\n", ueth_int_name);
        return RT_ERROR;
    }

    return RT_EOK;
}

void ueth_int_recv(void)
{
    channel_cmd_recv(ueth_int_channel);
}

void *ueth_v2p(void * addr)
{
    void* thread_self = rt_thread_self();
    int shmid = channel_compose_cmd3(UETH_V2P_REQ, (void*)0, thread_self, addr, 0);
    void *res = RT_NULL;
    struct channel_cmd *cmd  = (struct channel_cmd *)lwp_shmat(shmid, NULL);
    if (cmd) 
    {
        res = channel_cmd_send_recv(ueth_ueth_srv_channel, (void*)(size_t)shmid);
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
    return res;

}

void *ueth_remap(void * addr, int type, size_t size) 
{
    void* thread_self = rt_thread_self();
    int shmid = channel_compose_cmd4(UETH_REMAP_REQ, (void*)0, thread_self, (void*)type, addr, sizeof(size_t));
    void *res = RT_NULL;
    struct channel_cmd *cmd  = (struct channel_cmd *)lwp_shmat(shmid, NULL);
    if (cmd) 
    {
        memcpy(CHANNEL_CMD_DATA(cmd), (void*)&size, sizeof(size_t));
        res = channel_cmd_send_recv(ueth_ueth_srv_channel, (void*)(size_t)shmid);
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
    return res;
}

void ueth_gpioinit(void *gpio, size_t size) 
{
    int shmid = channel_compose_cmd1(UETH_GPIOINIT_REQ, (void*)0, size);
    struct channel_cmd *cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
    if (cmd)
    {
        memcpy(CHANNEL_CMD_DATA(cmd), gpio, size);
        channel_cmd_send_recv(ueth_ueth_srv_channel, (void *)(size_t)shmid);
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
}

void ueth_init_clock() 
{
    int shmid = channel_compose_cmd1(UETH_CLOCKINIT_REQ, (void*)0, 0);
    struct channel_cmd *cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
    if (cmd)
    {
        channel_cmd_send_recv(ueth_ueth_srv_channel, (void *)(size_t)shmid);
        lwp_shmdt(cmd);
    }

    lwp_shmrm(shmid);
}

void ueth_hw_interrupt_install(int vector, void * param) {
    int shmid = channel_compose_cmd3(UETH_INSTALL_INTERRUPT_REQ, (void*)0, (void*)vector, param, 0);
    struct channel_cmd *cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
    if (cmd)
    {
        channel_cmd_send_recv(ueth_ueth_srv_channel, (void *)(size_t)shmid);
        lwp_shmdt(cmd);
        
    }
    
    lwp_shmrm(shmid);
}