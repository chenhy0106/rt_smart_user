#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "channel.h"

static int _shm_key = -1;
int channel_compose_cmd(uint32_t cmd, void *arg0, void *arg1, void *arg2,
    void *arg3, void *arg4, void *arg5, size_t datalen)
{
    int shmid;
    void *shm_vaddr = NULL;
    struct channel_cmd *pcmd = NULL;

    /* the shared memory includes the command and the possible data */
    size_t len = datalen + CHANNEL_CMD_OFFSET;

    /* use the current thread ID to label the shared memory */
    if (_shm_key == -1)_shm_key = (int)(unsigned long)rt_thread_self();
    _shm_key = _shm_key + 2;

    shmid = lwp_shmget(_shm_key, len, 1);    /* create a new shared-memory */
    if (shmid == -1)
    {
        rt_kprintf("%s :Fail to allocate a shared memory! _shm_key %ld\n",__func__,_shm_key);
        return -1;
    }

    /* get the start address of the shared memory */
    shm_vaddr = lwp_shmat(shmid, NULL);
    if (shm_vaddr == NULL)
    {
        printf("The allocated shared memory doesn't have a valid address!\n");
        lwp_shmrm(shmid);
        return -1;
    }

    /* prepare the command structure */
    pcmd = (struct channel_cmd *) shm_vaddr;

    pcmd->cmd = cmd;
    pcmd->argv[0] = arg0;
    pcmd->argv[1] = arg1;
    pcmd->argv[2] = arg2;
    pcmd->argv[3] = arg3;
    pcmd->argv[4] = arg4;
    pcmd->argv[5] = arg5;

    lwp_shmdt(shm_vaddr);

    return shmid;
}

