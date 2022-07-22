#include "ipc_service.h"
#include <string.h>
#include <rtdef.h>
#define DBG_TAG "drv.enet"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#include <stdio.h>

static int ueth_ueth_srv_channel = -1;
const char *ueth_srv_name = "ueth_srv";

rt_inline rt_uint32_t rt_cpu_dcache_line_size_user(void)
{
    rt_uint32_t ctr;
    asm volatile ("mrc p15, 0, %0, c0, c0, 1" : "=r"(ctr));
    return 4 << ((ctr >> 16) & 0xF);
}

void rt_hw_cpu_dcache_invalidate_user(void *addr, int size)
{
    rt_uint32_t line_size = rt_cpu_dcache_line_size_user();
    rt_uint32_t start_addr = (rt_uint32_t)addr;
    rt_uint32_t end_addr = (rt_uint32_t) addr + size + line_size - 1;

    asm volatile ("dmb":::"memory");
    start_addr &= ~(line_size - 1);
    end_addr &= ~(line_size - 1);
    while (start_addr < end_addr)
    {
        asm volatile ("mcr p15, 0, %0, c7, c6, 1" :: "r"(start_addr));  /* dcimvac */
        start_addr += line_size;
    }
    asm volatile ("dsb":::"memory");
}

void rt_hw_cpu_dcache_clean_user(void *addr, int size)
{
    rt_uint32_t line_size = rt_cpu_dcache_line_size_user();
    rt_uint32_t start_addr = (rt_uint32_t)addr;
    rt_uint32_t end_addr = (rt_uint32_t) addr + size + line_size - 1;

    asm volatile ("dmb":::"memory");
    start_addr &= ~(line_size - 1);
    end_addr &= ~(line_size - 1);
    while (start_addr < end_addr)
    {
        asm volatile ("mcr p15, 0, %0, c7, c10, 1" :: "r"(start_addr)); /* dccmvac */
        start_addr += line_size;
    }
    asm volatile ("dsb":::"memory");
}

rt_err_t ipc_service_init()
{
    ueth_ueth_srv_channel = rt_channel_open(ueth_srv_name, O_RDWR);
    if (ueth_ueth_srv_channel < 0){
        printf("open %s failed\n", ueth_srv_name);
        return RT_ERROR;
    }

    return RT_EOK;
}

void *ueth_v2p(void * addr)
{
    void* thread_self = rt_thread_self();
    int shmid = channel_compose_cmd3(UETH_V2P, (void*)0, thread_self, addr, 0);
    void *res = RT_NULL;
    struct channel_cmd *cmd  = (struct channel_cmd *)lwp_shmat(shmid, NULL);
    if (cmd) 
    {
        res = channel_cmd_send_recv(ueth_ueth_srv_channel, (void*)(size_t)shmid);
        lwp_shmdt(cmd);
    }

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
}

void ueth_dcache_clean(void *paddr, size_t size)
{
    // int shmid = channel_compose_cmd3(UETH_DCACHE_REQ, (void*)0, (void*)UETH_DCACHE_CLEAN, paddr, sizeof(size_t));
    // struct channel_cmd *cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
    // if (cmd)
    // {
    //     memcpy(CHANNEL_CMD_DATA(cmd), (void*)&size, sizeof(size_t));
    //     channel_cmd_send_recv(ueth_ueth_srv_channel, (void *)(size_t)shmid);
    //     lwp_shmdt(cmd);
    // }
    // rt_hw_cpu_dcache_clean_user(paddr, size);
}

void ueth_dcache_invalid(void *paddr, size_t size)
{
    // int shmid = channel_compose_cmd3(UETH_DCACHE_REQ, (void*)0, (void*)UETH_DCACHE_INVALID, paddr, 0);
    // struct channel_cmd *cmd = (struct channel_cmd*)lwp_shmat(shmid, NULL);
    // if (cmd)
    // {
    //     memcpy(CHANNEL_CMD_DATA(cmd), (void*)&size, sizeof(size_t));
    //     channel_cmd_send_recv(ueth_ueth_srv_channel, (void *)(size_t)shmid);
    //     lwp_shmdt(cmd);
    // }
    // rt_hw_cpu_dcache_invalidate_user(paddr, size);
}