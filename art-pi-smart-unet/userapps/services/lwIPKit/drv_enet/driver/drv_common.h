/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-11     RiceChen     the first version
 *
 */

#ifndef __DRV_COMMON_H__
#define __DRV_COMMON_H__

#include <rtdef.h>
                                                                             
struct imx6ull_iomuxc
{
    rt_uint32_t muxRegister;
    rt_uint32_t muxMode;
    rt_uint32_t inputRegister;
    rt_uint32_t inputDaisy;
    rt_uint32_t configRegister;

    rt_uint32_t inputOnfield;

    rt_uint32_t configValue;
};

#define GET_ARRAY_NUM(ins)          ((uint32_t)(sizeof(ins)/sizeof(ins[0])))

#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
        
#endif