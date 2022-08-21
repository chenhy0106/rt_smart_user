#include "ueth.h"
#include <lwp_user_mm.h>
#include <drv_common.h>
#include <fsl_clock.h>

#include <stdio.h>

#define UETH_SRVTHREAD_STACKSIZE (1 << 15)
#define UETH_SRVTHREAD_PRIORITY 25

static int ueth_srv_channel = -1;
const char *ueth_srv_name = "ueth_srv";
static int ueth_int_channel = -1;
const char *ueth_int_name = "ueth_int";

extern void rt_hw_cpu_dcache_clean(void *addr, int size);
extern void rt_hw_cpu_dcache_invalidate(void *addr, int size);

#define SYS_PAGE_SIZE (4096U)
#define RECV_INT_MASK (ENET_EIR_RXF_MASK | ENET_EIR_RXB_MASK)
ENET_Type * enet_base = RT_NULL;
void ueth_irqhandle(int irq, void *base)
{
    ENET_Type * enet_base = (ENET_Type*)base;
    if (enet_base->EIMR & RECV_INT_MASK)
    {
        if (enet_base->EIR & RECV_INT_MASK)
        {
            enet_base->EIMR &= ~RECV_INT_MASK;
            ueth_cmd_send(ueth_int_channel, RT_NULL, 1);
        }
    }
}

void ueth_srv_entry(void * parameters) {
    struct channel_cmd *cmd;

    while (1)
    {
        int shmid = (int)(size_t)ueth_cmd_recv(ueth_srv_channel);
        if (shmid >= 0)
        {
            cmd = lwp_shminfo(shmid);
            switch (cmd->cmd)
            {
            case UETH_INSTALL_INTERRUPT_REQ:
            {
                int vector = (int)cmd->argv[1];
                void * param = cmd->argv[2];
                enet_base = (ENET_Type *)rt_ioremap_nocache(param, SYS_PAGE_SIZE);
                rt_hw_interrupt_install(vector, (rt_isr_handler_t)ueth_irqhandle, (void*)enet_base, "eth_irq");     
                rt_hw_interrupt_umask(vector);
                ueth_cmd_reply(ueth_srv_channel, RT_NULL);
                break;
            }
            case UETH_V2P_REQ:
            {   
                rt_thread_t tid = (rt_thread_t)cmd->argv[1];
                void *addr = cmd->argv[2];
                struct rt_lwp* lwp = tid->lwp;
                void *res = rt_hw_mmu_v2p(&lwp->mmu_info, addr);
                ueth_cmd_reply(ueth_srv_channel, res);
                break;
            }
            case UETH_REMAP_REQ:
            {
                rt_thread_t tid = (rt_thread_t)cmd->argv[1];
                struct rt_lwp* lwp = tid->lwp;
                int type = (int)cmd->argv[2];
                void *addr = cmd->argv[3];
                size_t size = *(size_t*)((void*)(size_t)cmd + WORKLOAD_START);
                void *res = RT_NULL;
                switch (type)
                {
                case UETH_REMAP:
                {
                    res = lwp_map_user_phy(lwp, RT_NULL, addr, size, 0);
                    break;
                }
                case UETH_UNMAP:
                {
                    lwp_unmap_user_phy(lwp, addr);
                    break;
                }
                case UETH_REMAP_NOCACHE:
                {
                    res = lwp_map_user_phy(lwp, RT_NULL, addr, size, 0);
                    break;
                }
                default:
                    break;
                }
                
                ueth_cmd_reply(ueth_srv_channel, res);
                break;
            }
            case UETH_GPIOINIT_REQ:
            {
                struct imx6ull_iomuxc *gpio = (struct imx6ull_iomuxc *)((void *)(size_t)cmd + WORKLOAD_START);
                imx6ull_gpio_init(gpio);
                ueth_cmd_reply(ueth_srv_channel, RT_NULL);
                break;
            }
            case UETH_CLOCKINIT_REQ:
            {
                const clock_enet_pll_config_t config = {true, true, false, 1, 1};
                CLOCK_InitEnetPll(&config);
                ueth_cmd_reply(ueth_srv_channel, RT_NULL);
                break;
            }
            case UETH_DCACHE_REQ:
            {
                int type = (int)cmd->argv[1];
                void * addr = cmd->argv[2];
                size_t size = *(size_t*)((void*)(size_t)cmd + WORKLOAD_START);
                switch (type)
                {
                case UETH_DCACHE_CLEAN:
                {
                    rt_hw_cpu_dcache_clean(addr, size);
                    break;
                }
                case UETH_DCACHE_INVALID:
                {
                    rt_hw_cpu_dcache_invalidate(addr, size);
                    break;
                }
                default:
                    break;
                }
                ueth_cmd_reply(ueth_srv_channel, RT_NULL);
                break;
            }
            default:
                break;
            }

            lwp_shmdt(cmd);
        }
    }

}

INIT_APP_EXPORT(init_ueth_srv);

int init_ueth_srv(void) {
    ueth_srv_channel  = rt_channel_open(ueth_srv_name, O_CREAT);
    if (ueth_srv_channel < 0) goto close_channel1;

    ueth_int_channel = rt_channel_open(ueth_int_name, O_CREAT);
    if (ueth_int_channel < 0) goto close_channel2;

    rt_thread_t tid = rt_thread_create("uethsrv", ueth_srv_entry, RT_NULL,
        UETH_SRVTHREAD_STACKSIZE, UETH_SRVTHREAD_PRIORITY, 10);
    if (tid) rt_thread_startup(tid);
    return 0;

close_channel1:
    rt_channel_close(ueth_srv_channel);
    ueth_srv_channel = -1;
    rt_kprintf("init_ueth_interface fail 1\n");
    return -1;
close_channel2:
    rt_channel_close(ueth_int_channel);
    ueth_int_channel = -1;
    rt_kprintf("init_ueth_interface fail 2\n");
    return -1;
}