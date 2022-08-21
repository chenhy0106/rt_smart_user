#include "unet.h"


static size_t key = 0;
int compose_cmd(uint32_t cmd, void *arg0, void *arg1, void *arg2,
        void *arg3, void *arg4, void *arg5, size_t datalen, struct unet_cmd **shm_vaddr)
{
    int shmid;

    /* the shared memory includes the command and the possible data */
    size_t len = datalen + UNET_CMD_OFFSET;

    /*
     * Usually use the current thread ID to label the shared memory, like this:
     * size_t key = (size_t) rt_thread_self();
     *
     * But we need to send commands to 2 channels, here is a simple way to avoid
     * ID conflicts.
     */
    key = key + 2;

    shmid = lwp_shmget(key, len, 1);    /* create a new shared-memory */
    if (shmid == -1)
    {
        rt_kprintf("Fail to allocate a shared memory, len = %d!\n", len);
        return -1;
    }

    /* get the start address of the shared memory */
    *shm_vaddr = lwp_shmat(shmid, RT_NULL);
    if (*shm_vaddr == RT_NULL)
    {
        rt_kprintf("The allocated shared memory doesn't have a valid address!\n");
        return -1;
    }

    /* prepare the command structure */
    struct unet_cmd *pcmd = (struct unet_cmd *) *shm_vaddr;
    pcmd->cmd = cmd;
    pcmd->argv[0] = arg0;
    pcmd->argv[1] = arg1;
    pcmd->argv[2] = arg2;
    pcmd->argv[3] = arg3;
    pcmd->argv[4] = arg4;
    pcmd->argv[5] = arg5;

    return shmid;
}
