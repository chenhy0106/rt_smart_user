#include "ipc_srv.h"
#include <lwp_user_mm.h>
#include <drv_common.h>
#include <fsl_clock.h>

static size_t key = 1;
int compose_cmd(uint32_t cmd, void *arg0, void *arg1, void *arg2,
        void *arg3, void *arg4, void *arg5, size_t datalen)
{
    int shmid;
    void *shm_vaddr;

    /* the shared memory includes the command and the possible data */
    size_t len = datalen + WORKLOAD_START;

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
    struct channel_cmd *pcmd = (struct channel_cmd *) shm_vaddr;
    pcmd->cmd = cmd;
    pcmd->argv[0] = arg0;
    pcmd->argv[1] = arg1;
    pcmd->argv[2] = arg2;
    pcmd->argv[3] = arg3;
    pcmd->argv[4] = arg4;
    pcmd->argv[5] = arg5;

    return shmid;
}

#define UETH_SRVTHREAD_STACKSIZE (1 << 15)
#define UETH_SRVTHREAD_PRIORITY 25

static int ipc_srv_channel = -1;
const char *ipc_srv_name = "ipc_srv";
static int ueth_int_channel = -1;
const char *ueth_int_name = "ueth_int";

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
            ipc_cmd_send(ueth_int_channel, RT_NULL, 1);
        }
    }
}

void ipc_srv_entry(void * parameters) {
    struct channel_cmd *cmd;

    while (1)
    {
        int shmid = (int)(size_t)ipc_cmd_recv(ipc_srv_channel);
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
                ipc_cmd_reply(ipc_srv_channel, RT_NULL);
                break;
            }
            case UETH_V2P_REQ:
            {   
                rt_thread_t tid = (rt_thread_t)cmd->argv[1];
                void *addr = cmd->argv[2];
                struct rt_lwp* lwp = tid->lwp;
                void *res = rt_hw_mmu_v2p(&lwp->mmu_info, addr);
                ipc_cmd_reply(ipc_srv_channel, res);
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
                
                ipc_cmd_reply(ipc_srv_channel, res);
                break;
            }
            case UETH_GPIOINIT_REQ:
            {
                struct imx6ull_iomuxc *gpio = (struct imx6ull_iomuxc *)((void *)(size_t)cmd + WORKLOAD_START);
                imx6ull_gpio_init(gpio);
                ipc_cmd_reply(ipc_srv_channel, RT_NULL);
                break;
            }
            case UETH_CLOCKINIT_REQ:
            {
                const clock_enet_pll_config_t config = {true, true, false, 1, 1};
                CLOCK_InitEnetPll(&config);
                ipc_cmd_reply(ipc_srv_channel, RT_NULL);
                break;
            }
            default:
                break;
            }

            lwp_shmdt(cmd);
        }
    }

}

int init_ipc_srv(void) {
    ipc_srv_channel  = rt_channel_open(ipc_srv_name, O_CREAT);
    if (ipc_srv_channel < 0) goto close_channel1;

    ueth_int_channel = rt_channel_open(ueth_int_name, O_CREAT);
    if (ueth_int_channel < 0) goto close_channel2;

    rt_thread_t tid = rt_thread_create("uethsrv", ipc_srv_entry, RT_NULL,
        UETH_SRVTHREAD_STACKSIZE, UETH_SRVTHREAD_PRIORITY, 10);
    if (tid) rt_thread_startup(tid);
    return 0;

close_channel1:
    rt_channel_close(ipc_srv_channel);
    ipc_srv_channel = -1;
    rt_kprintf("init_ipc_interface fail 1\n");
    return -1;
close_channel2:
    rt_channel_close(ueth_int_channel);
    ueth_int_channel = -1;
    rt_kprintf("init_ueth_interface fail 2\n");
    return -1;
}
INIT_APP_EXPORT(init_ipc_srv);
