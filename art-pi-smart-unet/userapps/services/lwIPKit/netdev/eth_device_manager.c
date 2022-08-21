#include "eth_device_manager.h"
#include <string.h>
#include <stdio.h>

typedef struct eth_device_node
{
    rt_device_t dev;
    char name[8];
} eth_device_node;

#define DEV_INIT (dev->ops->init)
#define DEV_CLOSE (dev->ops->close)
#define DEV_CONTROL (dev->ops->control)

#define MAX_DEV_NUM 3
static eth_device_node ueth_dev_list[MAX_DEV_NUM];
static char ueth_dev_list_valid[MAX_DEV_NUM];

rt_device_t ueth_device_find(const char *name)
{
    for (int i = 0; i < MAX_DEV_NUM; i++)
    {
        if (ueth_dev_list_valid[i])
        {
            if (strncmp(ueth_dev_list[i].name, name, 8) == 0)
            {  
                return ueth_dev_list[i].dev;
            }
        }
    }

    return RT_NULL;
}

rt_err_t ueth_device_register(rt_device_t dev, const char *name, rt_uint16_t flags)
{
    if (dev == RT_NULL)
        return -RT_ERROR;

    if (ueth_device_find(name) != RT_NULL)
        return -RT_ERROR;

    int ueth_dev_list_index = 0;
    while (ueth_dev_list_index < MAX_DEV_NUM)
    {
        if (!ueth_dev_list_valid[ueth_dev_list_index])
        {
            break;
        }
        ueth_dev_list_index++;
    }

    if (ueth_dev_list_index == MAX_DEV_NUM)
    {
        return -RT_ERROR;
    }
    
    strcpy(ueth_dev_list[ueth_dev_list_index].name, name);
    ueth_dev_list[ueth_dev_list_index].dev = dev;
    ueth_dev_list_valid[ueth_dev_list_index] = 1;
    dev->flag = flags;
    dev->ref_count = 0;
    dev->open_flag = 0;

    dev->parent.type = RT_Object_Class_Device;

    return RT_EOK;
}

rt_err_t ueth_device_unregister(rt_device_t dev)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->parent.type == RT_Object_Class_Device);

    for (int i = 0; i < MAX_DEV_NUM; i++)
    {
        if (ueth_dev_list_valid[i] && dev == ueth_dev_list[i].dev)
        {
            ueth_dev_list_valid[i] = 0;
        }
    }

    return RT_EOK;
}

rt_err_t ueth_device_init(rt_device_t dev)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->parent.type == RT_Object_Class_Device);

    /* get device_init handler */
    if (DEV_INIT != RT_NULL)
    {
        if (!(dev->flag & RT_DEVICE_FLAG_ACTIVATED))
        {
            result = DEV_INIT(dev);
            if (result != RT_EOK)
            {
                printf("To initialize device:%s failed. The error code is %ld\n",
                           dev->parent.name, result);
            }
            else
            {
                dev->flag |= RT_DEVICE_FLAG_ACTIVATED;
            }
        }
    }

    return result;
}

rt_err_t ueth_device_close(rt_device_t dev)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->parent.type == RT_Object_Class_Device);

    if (dev->ref_count == 0)
        return -RT_ERROR;

    dev->ref_count--;

    if (dev->ref_count != 0)
        return RT_EOK;

    /* call device_close interface */
    if (DEV_CLOSE != RT_NULL)
    {
        result = DEV_CLOSE(dev);
    }

    /* set open flag */
    if (result == RT_EOK || result == -RT_ENOSYS)
        dev->open_flag = RT_DEVICE_OFLAG_CLOSE;

    return result;
}

rt_err_t ueth_device_control(rt_device_t dev, int cmd, void *arg)
{
    RT_ASSERT(dev != RT_NULL);
    RT_ASSERT(dev->parent.type == RT_Object_Class_Device);

    /* call device_write interface */
    if (DEV_CONTROL != RT_NULL)
    {
        return DEV_CONTROL(dev, cmd, arg);
    }

    return -RT_ENOSYS;
}