/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-29     heyuanjie    first version
 * 2019-10-12     Jesven       Add MMU and userspace support
 * 2020-10-08     Bernard      Architecture and code cleanup
 * 2021-08-26     linzhenxing  add lwp_setcwd\lwp_getcwd
 */

/*
 * RT-Thread light-weight process
 */
#ifndef __LWP_H__
#define __LWP_H__

#include <stdint.h>

#include <rtthread.h>

#include <dfs.h>

typedef struct
{
    size_t *vtable;
    size_t vstart;
    size_t vend;
    size_t pv_off;
} rt_mmu_info;

#ifdef __cplusplus
extern "C" {
#endif

struct rt_lwp
{
#ifdef RT_USING_USERSPACE
    rt_mmu_info mmu_info;
    struct lwp_avl_struct *map_area;
    size_t end_heap;
#else
#ifdef ARCH_MM_MPU
    struct rt_mpu_info mpu_info;
#endif /* ARCH_MM_MPU */
#endif

#ifdef RT_USING_SMP
    int bind_cpu;
#endif

    uint8_t lwp_type;
    uint8_t reserv[3];

    struct rt_lwp *parent;
    struct rt_lwp *first_child;
    struct rt_lwp *sibling;

    rt_list_t wait_list;
    int32_t  finish;
    int  lwp_ret;

    void *text_entry;
    uint32_t text_size;
    void *data_entry;
    uint32_t data_size;

    int ref;
    void *args;
    uint32_t args_length;
    pid_t pid;
    pid_t __pgrp; /*Accessed via process_group()*/
    pid_t tty_old_pgrp;
    pid_t session;
    rt_list_t t_grp;

    int leader; /*boolean value for session group_leader*/
    struct dfs_fdtable fdt;
    char cmd[RT_NAME_MAX];

    int sa_flags;
    lwp_sigset_t signal;
    lwp_sigset_t signal_mask;
    int signal_mask_bak;
    rt_uint32_t signal_in_process;
    lwp_sighandler_t signal_handler[_LWP_NSIG];

    struct lwp_avl_struct *object_root;
    struct rt_mutex object_mutex;
    struct rt_user_context user_ctx;

    struct rt_wqueue wait_queue; /*for console */
    struct tty_struct *tty; /* NULL if no tty */

    struct lwp_avl_struct *address_search_head; /* for addressed object fast rearch */
    int debug;
    uint32_t bak_first_ins;
};

#endif
