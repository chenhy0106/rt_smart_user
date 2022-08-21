#ifndef ETH_DEVICE_MANAGER_H_
#define ETH_DEVICE_MANAGER_H_

#include <rtdef.h>
#include <rtthread.h>
#include <rtservice.h>

rt_err_t ueth_device_register(rt_device_t dev, const char *name, rt_uint16_t flags);
rt_err_t ueth_device_unregister(rt_device_t dev);
rt_err_t ueth_device_init(rt_device_t dev);
rt_device_t ueth_device_find(const char *name);
rt_err_t ueth_device_close(rt_device_t dev);
rt_err_t ueth_device_control(rt_device_t dev, int cmd, void *arg);

#endif