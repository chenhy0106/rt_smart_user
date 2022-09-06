#ifndef MBBUFF_H_
#define MBBUFF_H_

#include <rtdef.h>
#include <rtthread.h>
#include "arch/cirbuff.h"

struct rt_mailbox_buff
{
    rt_mailbox_t         mb;
    struct cirbuff      *cb;
};
typedef struct rt_mailbox_buff *rt_mailbox_buff_t;

// void tcpip_mb_timer_entry();
// rt_err_t sys_mbox_new(sys_mbox_t *mbox, int size);
// void sys_mbox_free(sys_mbox_t *mbox);
// rt_err_t post_msg(sys_mbox_t *mbox, void *msg);
// rt_err_t fetch_msg(sys_mbox_t *mbox, void **msg, u32_t t);

#endif