#ifndef __UETH_ETH_H__
#define __UETH_ETH_H__

#include <rtthread.h>
#include <rtdef.h>

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



#endif