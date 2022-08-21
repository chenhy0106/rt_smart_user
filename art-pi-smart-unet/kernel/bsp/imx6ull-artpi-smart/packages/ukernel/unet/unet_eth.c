/*
 * Copyright (c) 2011-2020, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-12     quanzhao     the first version
 */
#include <rtthread.h>
#include <rthw.h>       /* rt_hw_interrupt_disable/enable */
#include "unet_eth.h"

/* to use netdev */
#include <arpa/inet.h>
#include <netdev.h>

#define DBG_TAG "UNET"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_USERSPACE
#include <lwp_shm.h>    /* tranfer data through shared memories */
#endif

#include <ioremap.h>

static int unet_channel = -1;          /* kernel channel: handle commands from user */
static int unet_stack_channel = -1;    /* user channel: accept network requests */
static int unet_data_channel  = -1; /* user channel: accept input data */
static rt_uint64_t recv_wakeup_event_count[UNET_WAKEUP_EVENT_CNT];
/* obtain the channel to communicate with user-mode network stack */
int unet_get_stack_channel(void)
{
    /* the channel should be accessed only after initialization */
    return unet_stack_channel;
}
int unet_update_wakeup_event_cnt(int fd)
{
    rt_base_t level;
    if(fd >= UNET_WAKEUP_EVENT_CNT)
    {
        LOG_E("fd %d exceed limit value\n",fd);
        return -1;
    }
    level = rt_hw_interrupt_disable();
    recv_wakeup_event_count[fd]++;
    rt_hw_interrupt_enable(level);
    return 0;
}

int unet_get_wakeup_event_cnt(int fd,rt_uint64_t *event_cnt)
{
    rt_base_t level;
    if(fd >= UNET_WAKEUP_EVENT_CNT)
    {
        LOG_E("fd %d exceed limit value\n",fd);
        return -1;
    }
    level = rt_hw_interrupt_disable();
    *event_cnt = recv_wakeup_event_count[fd];
    rt_hw_interrupt_enable(level);
    return 0;
}

#ifndef UNET_ETHTHREAD_STACKSIZE
#define UNET_ETHTHREAD_STACKSIZE 8192
#endif

#define UNET_ETH_THREAD_PRIORITY   25

/* the maximum number of pending received mailbox entries to handle */
#define ETH_MBOX_SIZE   (16)

static struct rt_mailbox eth_rx_thread_mb;
ALIGN(4)
static rt_ubase_t eth_rx_thread_mb_pool[ETH_MBOX_SIZE];

/* NETDEV is an abstract layer for low-level devices, but also interacts with
 * UNET in user mode. It complicates the situation. */
#ifdef RT_USING_NETDEV

#include <netdev.h>

/* UNET requests to set the network interface up */
static int unet_netdev_set_up(struct netdev *netdev)
{
    struct eth_device *eth = (struct eth_device *)netdev->user_data;
    int shmid = compose_cmd3(UNET_SRV_SET_HW_STATUS, netdev, eth->netif, (void *)1, 0);
    unet_cmd_send(unet_stack_channel, (void *)(size_t)shmid);
    return RT_EOK;
}

/* UNET requests to set the network interface down */
static int unet_netdev_set_down(struct netdev *netdev)
{
    struct eth_device *eth = (struct eth_device *)netdev->user_data;
    int shmid = compose_cmd3(UNET_SRV_SET_HW_STATUS, netdev, eth->netif, (void *)0, 0);
    unet_cmd_send(unet_stack_channel, (void *)(size_t)shmid);
    return RT_EOK;
}

/* UNET requests to set the user network addresses */
static int unet_netdev_set_addr_info(struct netdev *netdev, ip_addr_t *ip_addr, ip_addr_t *netmask, ip_addr_t *gw)
{
    struct eth_device *eth = (struct eth_device *)netdev->user_data;
    int shmid = compose_cmd5(UNET_SRV_SET_ADDR_INFO, netdev, eth->netif,
            RT_NULL, RT_NULL, RT_NULL, 3*sizeof(ip_addr_t));
    if (shmid < 0)
        return -1;

    /* conver the pointers to offsets and copy the addresses into the page */
    struct unet_cmd *unet_cmd = lwp_shminfo(shmid);

    if (ip_addr)
    {
        unet_cmd->argv[2] = (void *)(size_t)UNET_CMD_OFFSET;
        rt_memcpy((void *)unet_cmd + (size_t)unet_cmd->argv[2], ip_addr, sizeof(ip_addr_t));
    }

    if (netmask)
    {
        unet_cmd->argv[3] = (void *)(UNET_CMD_OFFSET + sizeof(ip_addr_t));
        rt_memcpy((void *)unet_cmd + (size_t)unet_cmd->argv[3], netmask, sizeof(ip_addr_t));
    }

    if (gw)
    {
        unet_cmd->argv[4] = (void *)(UNET_CMD_OFFSET + 2*sizeof(ip_addr_t));
        rt_memcpy((void *)unet_cmd + (size_t)unet_cmd->argv[4], gw, sizeof(ip_addr_t));
    }

    /* We must not block this operation. */
    unet_cmd_send(unet_stack_channel, (void *)(size_t)shmid);

    return RT_EOK;
}

/* UNET requests to set the user network DNS */
static int unet_netdev_set_dns_server(struct netdev *netdev, uint8_t dns_num, ip_addr_t *dns_server)
{
    struct eth_device *eth = (struct eth_device *)netdev->user_data;
    int shmid = compose_cmd4(UNET_SRV_SET_DNS_SERVER, netdev, eth->netif,
            (void *)(size_t)dns_num, (void *)(size_t)UNET_CMD_OFFSET, dns_num*sizeof(ip_addr_t));
    struct unet_cmd *unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    rt_memcpy((void *)unet_cmd + (size_t)unet_cmd->argv[2], dns_server, dns_num*sizeof(ip_addr_t));

    unet_cmd_send(unet_stack_channel, (void *)(size_t)shmid);

    return RT_EOK;
}

/* UNET requests to set the IP address dynamically or statically */
static int unet_netdev_set_dhcp(struct netdev *netdev, rt_bool_t is_enabled)
{
    struct eth_device *eth = (struct eth_device *)netdev->user_data;
    int shmid = compose_cmd3(UNET_SRV_SET_DHCP, netdev, eth->netif, (void *)(size_t)is_enabled, 0);
    unet_cmd_send(unet_stack_channel, (void *)(size_t)shmid);
    return RT_EOK;
}

int unet_netdev_set_default(struct netdev *netdev)
{
    struct eth_device *eth = (struct eth_device *)netdev->user_data;
    int shmid = compose_cmd2(UNET_SRV_SET_DEFAULT, netdev, eth->netif, 0);
    unet_cmd_send(unet_stack_channel, (void *)(size_t)shmid);
    return RT_EOK;
}

#include <netdb.h>

int unet_netdev_ping(struct netdev *netdev, const char *host, size_t data_len,
    uint32_t timeout, struct netdev_ping_resp *ping_resp)
{
    int result = 0;
    ip_addr_t target_addr;
    int shmid;
    struct unet_cmd *unet_cmd;
    struct addrinfo hint, *res = RT_NULL;
    struct sockaddr_in *h = RT_NULL;
    struct in_addr ina;

    RT_ASSERT(netdev);
    RT_ASSERT(host);
    RT_ASSERT(ping_resp);

    rt_memset(&hint, 0x00, sizeof(hint));
    /* convert URL to IP */
    if (unet_getaddrinfo(host, RT_NULL, &hint, &res) != 0)
    {
        return -RT_ERROR;
    }
    rt_memcpy(&h, &res->ai_addr, sizeof(struct sockaddr_in *));
    rt_memcpy(&ina, &h->sin_addr, sizeof(ina));
    unet_freeaddrinfo(res);

    if (inet_aton(inet_ntoa(ina), &target_addr) == 0)
    {
        rt_kprintf("Cannot recogize the IP address %s.\n", host);
        return -RT_ERROR;
    }

    shmid = compose_cmd3(UNET_SRV_PING, RT_NULL, (void*)data_len, (void *)(size_t)timeout, sizeof(ip_addr_t));
    if (shmid < 0) return -RT_ENOMEM;

    /* copy the second parameter */
    unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);
    unet_cmd->argv[0] = (void *)(size_t)UNET_CMD_OFFSET;
    rt_memcpy((void *)(unet_cmd + 1), &target_addr, sizeof(ip_addr_t));

    result = (int)(size_t)unet_cmd_send_recv(unet_stack_channel, (void *)(size_t)shmid);
    if (result == 0)
    {
        rt_memcpy(&(ping_resp->ip_addr), (void*)(unet_cmd + 1), sizeof(ip_addr_t));
        ping_resp->data_len  = (uint16_t)((int)(size_t)unet_cmd->argv[1]);
        ping_resp->ttl       = (uint16_t)((int)(size_t)unet_cmd->argv[2]);
        ping_resp->ticks     = (uint32_t)((int)(size_t)unet_cmd->argv[3]);
        ping_resp->user_data = RT_NULL;
    }
    else
    {
        result = -RT_ETIMEOUT;
    }

    lwp_shmrm(shmid);
    return result;
}

/* netdev operations to userspace network */
const struct netdev_ops unet_netdev_ops =
{
    unet_netdev_set_up,
    unet_netdev_set_down,

    unet_netdev_set_addr_info,
    unet_netdev_set_dns_server,
    unet_netdev_set_dhcp,
#ifdef RT_USING_FINSH
    unet_netdev_ping,
    NULL,   /* netstat */
#endif
    unet_netdev_set_default
};

#endif /* RT_USING_NETDEV */


#define MAX_UETH_DEVICE_NUM 3
static void* ueth_device_vaddr[MAX_UETH_DEVICE_NUM];
static void* ueth_device_paddr[MAX_UETH_DEVICE_NUM];
static void* ueth_device_p2v(void* paddr)
{
    int i = 0;
    for (i = 0; i < MAX_UETH_DEVICE_NUM; i++)
    {
        if (ueth_device_paddr[i] == paddr)
        {
            return ueth_device_vaddr[i];
        }
    }

    for (i = 0; i < MAX_UETH_DEVICE_NUM; i++)
    {
        if (ueth_device_paddr[i] == 0)
        {
            break;
        }
    }

    if (i == MAX_UETH_DEVICE_NUM)
    {
        return 0;
    }

    rt_device_t vaddr = (rt_device_t)rt_ioremap_cached(paddr, sizeof(struct rt_device));
    ueth_device_paddr[i] = paddr;
    ueth_device_vaddr[i] = vaddr;
    return vaddr;
}


extern int sal_unet_netdev_set_pf_info(struct netdev *netdev);
/*
 * In the microkernel, the kernel couldn't complete all the tasks alone, which
 * must interact with UNET running in the user mode. This thread waits for the
 * command from UNET and do the low-level operations, even including the
 * unfinished initialization!.
 *
 * To avoid confusing with the commands from kernel to unet (through unet_srv),
 * the numbers of all the commands received are negative.
 */
static void unet_channel_entry(void* parameter)
{
    int    shmid = -1;  /* shared-memory handler */
    struct unet_cmd *unet_cmd;
    struct netdev *netdev = RT_NULL;

    /* channel available */
    if (unet_channel < 0) return ;

    while(1)
    {
        unet_cmd = RT_NULL;
        shmid = (int)(size_t) unet_cmd_recv(unet_channel);
        if (shmid >= 0)
        {
            unet_cmd = (struct unet_cmd *)lwp_shminfo(shmid);

            /* check the received command */
            if(unet_cmd == RT_NULL)
            {
                rt_kprintf("Receive an unet_eth command at the wrong position.\n");
                continue;
            }
        }
        else
        {
            rt_kprintf("%s line %d read unet channel error\n",__func__,__LINE__);
        }

        /* handle the command */
        switch(unet_cmd->cmd)
        {

            case UNET_TCPIP_STACK_ATTACH:
            {
                int ack = 0;
                const char *channel_name = (const char *)((rt_uint8_t*)unet_cmd + (int)(size_t)unet_cmd->argv[0]);
                const char *data_name    = (const char *)((rt_uint8_t*)unet_cmd + (int)(size_t)unet_cmd->argv[1]);

                unet_stack_channel = rt_channel_open(channel_name, O_RDWR);
                unet_data_channel  = rt_channel_open(data_name, O_RDWR);

                if ((unet_stack_channel >= 0) && (unet_data_channel >= 0))
                {
                    ack = 0;
                }
                else
                {
                    ack = -1;

                    /* close channel if these channels are opended */
                    if (unet_stack_channel >= 0)
                    {
                        rt_channel_close(unet_stack_channel);
                        unet_stack_channel = -1;
                    }

                    if (unet_data_channel >= 0)
                    {
                        rt_channel_close(unet_data_channel);
                        unet_data_channel = -1;
                    }
                }

                unet_cmd_reply(unet_channel, (void*)(size_t)ack);
                break;
            }

            case UNET_TCPIP_STACK_DETACH:
                break;

            case UNET_NETDEV_NETIF_ATTACH:
            {
                /* attach the netif in user space to the netdev in kernel */
                struct netdev *netdev = RT_NULL;
                struct eth_device *eth_device = RT_NULL;

                const char *name = (const char *)(unet_cmd + 1);
                rt_kprintf("***********%s %d %s\n", __FILE__, __LINE__, name);
                struct rt_device *device = rt_device_find(name);
                rt_kprintf("***********%s %d %p\n", __FILE__, __LINE__, device);
                if (device)
                {
                    eth_device = (struct eth_device*)device;
                    if (device->type == RT_Device_Class_NetIf)
                    {
                        /* allocate a new netdev */
                        netdev = (struct netdev *)rt_calloc(1, sizeof(struct netdev));
                        if (netdev == RT_NULL)
                        {
                            LOG_E("out of memory");
                            break;
                        }

                        sal_unet_netdev_set_pf_info(netdev);
                        /* register the netdev with net device as its user data,
                         * so now, netdev (user_data)->eth_device (netif)->netif. */
                        netdev_register(netdev, name, eth_device);

                        /* Update netdev info after registered */
                        netdev->flags = eth_device->flags;
                        netdev->mtu = 1500;
                        netdev->ops = &unet_netdev_ops;
                        netdev->hwaddr_len = 6;
                        rt_kprintf("***********%s %d %p\n", __FILE__, __LINE__, device);
                        rt_device_control(device, NIOCTL_GADDR, netdev->hwaddr);
                        rt_kprintf("***********%s %d\n", __FILE__, __LINE__);

                        netdev_low_level_set_dhcp_status(netdev, RT_TRUE);
                        rt_kprintf("***********%s %d\n", __FILE__, __LINE__);
                    }
                }
                else
                {
                    LOG_I("no device:%s found!", name);
                }

                unet_cmd_reply(unet_channel, netdev);
                break;
            }
            case UNET_NETDEV_NETIF_DETACH:
            {
                const char *name = (const char *)(unet_cmd + 1);
                struct netdev *netdev = unet_cmd->argv[0];
                void *netif = NULL;

                struct rt_device *device = rt_device_find(name);
                if (device && netdev->user_data == device)
                {
                    struct eth_device *eth_device;
                    eth_device = (struct eth_device*)device;

                    netif = eth_device->netif;
                    eth_device->netif = NULL;
                    netdev_unregister(netdev);
                    rt_free(netdev);

                }
                else
                {
                    LOG_I("device %s was invalid or not registered as netdev!", name);
                }

                unet_cmd_reply(unet_channel, netif);
                break;
            }

            case UNET_NETDEV_SET_STATUS:    /* NETDEV_FLAG_UP */
            {
                netdev = (struct netdev *)unet_cmd->argv[0];
                rt_bool_t updown = (rt_bool_t)(size_t)unet_cmd->argv[1];

                netdev_low_level_set_status(netdev, updown);
                unet_cmd_reply(unet_channel, RT_NULL);
                break;
            }

            case UNET_NETDEV_SET_LINKSTATUS:/* NETDEV_FLAG_LINK_UP, no reply */
            {
                netdev = (struct netdev *)unet_cmd->argv[0];
                rt_bool_t updown = (rt_bool_t)(size_t)unet_cmd->argv[1];

                netdev_low_level_set_link_status(netdev, updown);
                lwp_shmrm(shmid);
                break;
            }

            case UNET_NETDEV_SET_DHCP:      /* NETDEV_FLAG_DHCP */
            {
                netdev = (struct netdev *)unet_cmd->argv[0];
                rt_bool_t is_enabled = (rt_bool_t)(size_t)unet_cmd->argv[1];

                netdev_low_level_set_dhcp_status(netdev, is_enabled);
                lwp_shmrm(shmid);
                break;
            }

            case UNET_NETDEV_SETIPADDR:
            {
                ip_addr_t *ip_addr;
                netdev = (struct netdev *)unet_cmd->argv[0];
                if (unet_cmd->argv[1])
                    ip_addr = (ip_addr_t *)((void *)unet_cmd + (int)(size_t)unet_cmd->argv[1]);
                else
                    ip_addr = RT_NULL;

                netdev_low_level_set_ipaddr(netdev, ip_addr);
                unet_cmd_reply(unet_channel, RT_NULL);
                break;
            }

            case UNET_NETDEV_SETNETMASK:
            {
                ip_addr_t *netmask;
                netdev = (struct netdev *)unet_cmd->argv[0];
                if (unet_cmd->argv[1])
                    netmask = (ip_addr_t *)((void *)unet_cmd + (int)(size_t)unet_cmd->argv[1]);
                else
                    netmask = RT_NULL;

                netdev_low_level_set_netmask(netdev, netmask);
                unet_cmd_reply(unet_channel, RT_NULL);
                break;
            }

            case UNET_NETDEV_SETGW:
            {
                ip_addr_t *gw;
                netdev = (struct netdev *)unet_cmd->argv[0];
                if (unet_cmd->argv[1])
                    gw = (ip_addr_t *)((void *)unet_cmd + (int)(size_t)unet_cmd->argv[1]);
                else
                    gw = RT_NULL;

                netdev_low_level_set_gw(netdev, gw);
                unet_cmd_reply(unet_channel, RT_NULL);
                break;
            }

            case UNET_NETDEV_SET_DNS:
            {
                rt_uint8_t dns_num;
                ip_addr_t *dns;

                netdev = (struct netdev *)unet_cmd->argv[0];
                dns_num = (rt_uint8_t)(size_t)unet_cmd->argv[1];
                dns = (ip_addr_t *)((void *)unet_cmd + (int)(size_t)unet_cmd->argv[2]);

                netdev_low_level_set_dns_server(netdev, dns_num, dns);
                unet_cmd_reply(unet_channel, RT_NULL);
                break;
            }

            case UNET_WAKEUP_REQUEST:
            {
                extern int sock_wqueue_wakeup(void *sock);

                int lwip_fd = (int)(size_t)(size_t)unet_cmd->argv[1];
                unet_update_wakeup_event_cnt(lwip_fd);
                sock_wqueue_wakeup(unet_cmd->argv[0]);
                lwp_shmrm(shmid);

                break;
            }

            default:
                LOG_E("Receive an invalid unet_eth command: 0x%x, ignored.", unet_cmd->cmd);
                break;
        }
    }   /* while */
}

/* Initialize and register the ethernet device. */
rt_err_t eth_device_init(struct eth_device *eth, const char *name)
{
    rt_device_t dev = (rt_device_t)eth;
    dev->type = RT_Device_Class_NetIf;
    dev->rx_indicate = RT_NULL;
    dev->tx_complete = RT_NULL;

    rt_device_register(dev, name, RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}

/*
 * shared memory buffer
 *
 * Only one network interface is assumed. Protection is needed.
 */
static struct {
    int shmid;
    struct unet_cmd *cmd;
} shm_array[ETH_MBOX_SIZE];

static int in_idx = 0;  /* the first free entry */
static int out_idx = 0; /* the next entry to send */
static int is_full = 0;

void eth_device_prepare(void **data, int **datalen)
{
    if (in_idx != out_idx || is_full == 0)
    {
        *data = (void *)&shm_array[in_idx].cmd[1];
        *datalen = (int *)&shm_array[in_idx].cmd->argv[2];
        in_idx = (in_idx + 1) % ETH_MBOX_SIZE;
        is_full = (in_idx == out_idx);
    }
    else
    {
        rt_kprintf("in_idx %d out_idx %d if_full %d\n",in_idx,out_idx,is_full);
        *data = RT_NULL;
        *datalen = RT_NULL;
    }

    /*
     * If the user-mode lwip is not running, the shared-memory array becomes
     * full soon. After that, all received data are dumped without any
     * notifications.
     */
}

/* Invoked every time the ethernet device receives a packet. */
rt_err_t eth_device_ready(struct eth_device* dev)
{
    if (dev->netif)
        /* post message to Ethernet thread */
        return rt_mb_send(&eth_rx_thread_mb, (rt_ubase_t)dev);
    else
        return -RT_ERROR; /* netif is not initialized yet, just return. */
}

static void eth_rx_entry(void* parameter)
{
    struct eth_device *device;
    struct unet_cmd *cmd;

    void *buffer_ptr = RT_NULL;
    int *length_ptr = RT_NULL;

    while (1)
    {
        if (rt_mb_recv(&eth_rx_thread_mb, (rt_ubase_t *)&device, RT_WAITING_FOREVER) == RT_EOK)
        {

            while(1)
            {
                if((buffer_ptr == RT_NULL) || (length_ptr == RT_NULL))
                {
                    eth_device_prepare(&buffer_ptr,&length_ptr);
                }    

                if((buffer_ptr != RT_NULL) && (length_ptr != RT_NULL))
                {
                    *length_ptr = device->parent.ops->read((rt_device_t)device,0,buffer_ptr,0);
                    if(*length_ptr == 0)
                    {
                        break;
                    }
                }
                else
                {
                    LOG_E("can not get vaild shm buffer\n");
                    break;
                }
                buffer_ptr = RT_NULL;
                length_ptr = RT_NULL;

                if (out_idx == in_idx && !is_full)
                {
                    LOG_E("A input data notificaiton is recevied, but no data.");
                    break;
                }
                else
                {
                    /*
                    * A bug here. The device gives a notification may not be the
                    * one prepared data. But since we assume there is only one
                    * network device ... Fix this later.
                    */
                    cmd = shm_array[out_idx].cmd;
                    cmd->argv[0] = (void*)&device->parent;
                    cmd->argv[1] = (void*)device->netif;

                    /* notify to user stack and no ack */
                    unet_cmd_send_recv(unet_data_channel, (void *)(size_t)shm_array[out_idx].shmid);
                    out_idx = (out_idx + 1) % ETH_MBOX_SIZE;
                    is_full = 0;
                }
            }    

        }
        else
        {
            LOG_E("recv mb error.");
        }
    }
}

extern rt_err_t sock_wqueue_init(void);
int unet_init(void)
{
    rt_err_t result;
    rt_thread_t tid;
    /* initialize mailbox and create Ethernet Rx thread */
    result = rt_mb_init(&eth_rx_thread_mb, "ethrxmb",
                        &eth_rx_thread_mb_pool[0], ETH_MBOX_SIZE,
                        RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        RT_ASSERT(0);
    }

    int i;
    for (i = 0; i < ETH_MBOX_SIZE; i++)
    {
        int shmid = compose_cmd3(UNET_SRV_DATA_INPUT, NULL, NULL, NULL, 2048);
        if (shmid < 0)
        {
            LOG_E("Failed to allocate the shared memory.");
            break;
        }

        struct unet_cmd *cmd = (struct unet_cmd *)lwp_shminfo(shmid);
        if (!cmd)
        {
            LOG_E("Failed to get the shared memory address.");
            break;
        }

        shm_array[i].shmid  = shmid;
        shm_array[i].cmd    = cmd;
    }
    if (i != ETH_MBOX_SIZE)
    {
        LOG_E("ETH_MBOX_SIZE (%d) shared memories are required.", ETH_MBOX_SIZE);
        LOG_E("However, only (%d) shared memories are allocated.", i);
        LOG_E("Release all the existing shared memories. Exit.");
        while (i >= 0)
        {
            if (shm_array[i].shmid >= 0)
                lwp_shmrm(shm_array[i].shmid);
            i--;
        }
        return RT_ENOMEM;
    }
    /* initialize the sock waitqueue */
    sock_wqueue_init();

    /* create unet channel */
    // unet_channel = rt_channel_open("unet", O_CREAT);
    // if (unet_channel < 0)
    {
        // LOG_E("create channel failed!");
        // return -1;
    }
    // tid = rt_thread_create("ethrx", eth_rx_entry, RT_NULL,
    //     UNET_ETHTHREAD_STACKSIZE, UNET_ETH_THREAD_PRIORITY, 10);
    // if (tid) rt_thread_startup(tid);

    // tid = rt_thread_create("unet", unet_channel_entry, RT_NULL,
    //     UNET_ETHTHREAD_STACKSIZE, UNET_ETH_THREAD_PRIORITY - 1, 10);
    // if (tid) rt_thread_startup(tid);

    return RT_EOK;
}
INIT_APP_EXPORT(unet_init);

