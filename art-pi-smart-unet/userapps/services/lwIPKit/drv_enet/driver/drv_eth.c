/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-06-16     songchao   support emac driver
 * 2021-06-29     songchao   add phy link detect
 * 2021-08-13     songchao   support dual mac and reduse copy
 */

#include "drv_eth.h"
#define DBG_TAG "drv.enet"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <stdio.h>
#include <lwp_shm.h>

#define BSP_USING_IMX6ULL_ART_PI
#ifdef BSP_USING_IMX6ULL_ART_PI

static struct imx6ull_iomuxc mdio_gpio[2] = 
{
    {IOMUXC_GPIO1_IO06_ENET1_MDIO,0U,0xB029},
    {IOMUXC_GPIO1_IO07_ENET1_MDC,0U,0xB0E9}
};
#else
static struct imx6ull_iomuxc mdio_gpio[2] = 
{
    {IOMUXC_GPIO1_IO06_ENET2_MDIO,0U,0xB029},
    {IOMUXC_GPIO1_IO07_ENET2_MDC,0U,0xB0E9},
};
#endif
enum 
{
#ifdef RT_USING_ENET1
    DEV_ENET1,
#endif

#ifdef RT_USING_ENET2
    DEV_ENET2,
#endif

    DEV_ENET_MAX,
};

static struct rt_imx6ul_ethps _imx6ul_eth_device[DEV_ENET_MAX] = 
{
#ifdef RT_USING_ENET1
    {
        .dev_addr = {0xa8,0x5e,0x45,0x91,0x92,0x93},
        .mac_name = "e1",
        .irq_name = "emac1_intr",
        .enet_phy_base_addr = ENET1,
        .irq_num = IMX_INT_ENET1,
        .phy_num = ENET_PHY1,
        .mac_num = 1,
        .phy_base_addr = GPIO5,
        .phy_gpio_pin = 9,
        .phy_id = 7,
        .buffConfig =
        {
            ENET_RXBD_NUM,
            ENET_TXBD_NUM,
            ENET_RXBUFF_ALIGN_SIZE,
            ENET_TXBUFF_ALIGN_SIZE,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            ENET_RXBUFF_TOTAL_SIZE,
            ENET_TXBUFF_TOTAL_SIZE
        },
        .gpio = 
        {
            {IOMUXC_SNVS_SNVS_TAMPER9_GPIO5_IO09,0U,0x110B0},
            {IOMUXC_ENET1_RX_DATA0_ENET1_RDATA00,0U,0xB0E9},
            {IOMUXC_ENET1_RX_DATA1_ENET1_RDATA01,0U,0xB0E9},
            {IOMUXC_ENET1_RX_EN_ENET1_RX_EN,0U,0xB0E9},
            {IOMUXC_ENET1_RX_ER_ENET1_RX_ER,0U,0xB0E9},
            {IOMUXC_ENET1_TX_CLK_ENET1_REF_CLK1,1U,0x00F0},
            {IOMUXC_ENET1_TX_DATA0_ENET1_TDATA00,0U,0xB0E9},
            {IOMUXC_ENET1_TX_DATA1_ENET1_TDATA01,0U,0xB0E9},
            {IOMUXC_ENET1_TX_EN_ENET1_TX_EN,0U,0xB0E9}
        }
    },
#endif

#ifdef RT_USING_ENET2
    {
        .dev_addr = {0xa8,0x5e,0x45,0x01,0x02,0x03},
        .mac_name = "e2",
        .irq_name = "emac2_intr",
        .enet_phy_base_addr = ENET2,
        .irq_num = IMX_INT_ENET2,
        .phy_num = ENET_PHY2,
        .mac_num = 2,
        .phy_base_addr = GPIO5,
        .phy_gpio_pin = 6,
        .phy_id = 7,
        .buffConfig =
        {
            ENET_RXBD_NUM,
            ENET_TXBD_NUM,
            ENET_RXBUFF_ALIGN_SIZE,
            ENET_TXBUFF_ALIGN_SIZE,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            RT_NULL,
            ENET_RXBUFF_TOTAL_SIZE,
            ENET_TXBUFF_TOTAL_SIZE
        },
        .gpio = 
        {
            {IOMUXC_SNVS_SNVS_TAMPER6_GPIO5_IO06,0U,0x110B0},
            {IOMUXC_ENET2_RX_DATA0_ENET2_RDATA00,0U,0xB0E9},
            {IOMUXC_ENET2_RX_DATA1_ENET2_RDATA01,0U,0xB0E9},
            {IOMUXC_ENET2_RX_EN_ENET2_RX_EN,0U,0xB0E9},
            {IOMUXC_ENET2_RX_ER_ENET2_RX_ER,0U,0xB0E9},
            {IOMUXC_ENET2_TX_CLK_ENET2_REF_CLK2,1U,0x00F0},
            {IOMUXC_ENET2_TX_DATA0_ENET2_TDATA00,0U,0xB0E9},
            {IOMUXC_ENET2_TX_DATA1_ENET2_TDATA01,0U,0xB0E9},
            {IOMUXC_ENET2_TX_EN_ENET2_TX_EN,0U,0xB0E9}
        }

    },
#endif
};

#ifdef RT_USING_LWIP
#define eth_device_linkchange(x, y) eth_device_linkchange(x, y)
#else
#define eth_device_linkchange(x, y)
#endif

void imx6ul_eth_link_change(struct rt_imx6ul_ethps *imx6ul_device,rt_bool_t up)
{
    if(up)
    {
        LOG_D("enet%d link up",imx6ul_device->mac_num);
        eth_device_linkchange(&imx6ul_device->parent, RT_TRUE);
        imx6ul_device->phy_link_status = RT_TRUE;
    }
    else
    {
        LOG_D("enet%d link down",imx6ul_device->mac_num);
        eth_device_linkchange(&imx6ul_device->parent, RT_FALSE);
        imx6ul_device->phy_link_status = RT_FALSE;
    }
}

void page_alloc(size_t memsize, void **addr)
{
    size_t alloc_size = memsize + SYS_PAGE_SIZE * 2;
    void * addr_start = malloc(alloc_size);
    rt_memset(addr_start, 0, alloc_size);

    long mask = SYS_PAGE_SIZE - 1;
    *addr = (void*)((long)(addr_start + SYS_PAGE_SIZE) & ~mask);

    return;
}

rt_err_t enet_buffer_init(enet_buffer_config_t *buffConfig)
{
    void *tx_buff_addr = RT_NULL;
    void *rx_buff_addr = RT_NULL;
    void *tx_bd_addr = RT_NULL;
    void *rx_bd_addr = RT_NULL;

    if(((SYS_PAGE_SIZE<<RX_BUFFER_INDEX_NUM)<buffConfig->rxBufferTotalSize)||
       ((SYS_PAGE_SIZE<<TX_BUFFER_INDEX_NUM)<buffConfig->txBufferTotalSize))
    {
        LOG_E("ERROR: alloc mem not enough for enet driver");
        return RT_ERROR;
    }

    size_t rx_buff_memsize = SYS_PAGE_SIZE<<RX_BUFFER_INDEX_NUM;
    size_t tx_buff_memsize = SYS_PAGE_SIZE<<TX_BUFFER_INDEX_NUM;
    size_t rx_bd_memsize = SYS_PAGE_SIZE<<RX_BD_INDEX_NUM;
    size_t tx_bd_memsize = SYS_PAGE_SIZE<<TX_BD_INDEX_NUM;
    size_t total_memsize = rx_buff_memsize + tx_buff_memsize + rx_bd_memsize + tx_bd_memsize;

    void *mem_align= RT_NULL;
    page_alloc(total_memsize, &mem_align);
    if (!mem_align)
    {
        return RT_ERROR;
    }
    
    rx_buff_addr = mem_align;
    mem_align += rx_buff_memsize;
    if(!rx_buff_addr)
    {
        LOG_E("ERROR: rx buff page alloc failed");
        return RT_ERROR;
    }
    buffConfig->rxBufferAlign = rx_buff_addr;
    buffConfig->rxPhyBufferAlign = ueth_v2p(rx_buff_addr);
    
    tx_buff_addr = mem_align;
    mem_align += tx_buff_memsize;
    if(!tx_buff_addr)
    {
        LOG_E("ERROR: tx buff page alloc failed");
        return RT_ERROR;
    }
    buffConfig->txBufferAlign = tx_buff_addr;
    buffConfig->txPhyBufferAlign = ueth_v2p(tx_buff_addr);
    
    rx_bd_addr = mem_align;
    mem_align += rx_bd_memsize;
    if(!rx_bd_addr)
    {
        LOG_E("ERROR: rx bd page alloc failed");
        return RT_ERROR;
    }
    buffConfig->rxPhyBdStartAddrAlign = ueth_v2p(rx_bd_addr);
    buffConfig->rxBdStartAddrAlign = ueth_remap(buffConfig->rxPhyBdStartAddrAlign, UETH_REMAP_NOCACHE, rx_bd_memsize);
    
    tx_bd_addr = mem_align;
    if(!tx_bd_addr)
    {
        LOG_E("ERROR: tx bd page alloc failed");
        return RT_ERROR;
    }
    buffConfig->txPhyBdStartAddrAlign = ueth_v2p(tx_bd_addr);
    buffConfig->txBdStartAddrAlign = ueth_remap(buffConfig->txPhyBdStartAddrAlign, UETH_REMAP_NOCACHE, tx_bd_memsize);
    
    return RT_EOK;
}

/* EMAC initialization function */
static rt_err_t rt_imx6ul_eth_init(rt_device_t dev)
{
    rt_err_t state;
    struct rt_imx6ul_ethps *imx6ul_device = (struct rt_imx6ul_ethps *)dev;
    ENET_Type *base_addr = RT_NULL;
    enet_config_t *config;
    enet_handle_t *handle;
    enet_buffer_config_t *buffConfig;
    rt_uint32_t reg_value;

    // imx6ul_device->enet_virtual_base_addr = (ENET_Type *)rt_ioremap((void *)imx6ul_device->enet_phy_base_addr, SYS_PAGE_SIZE);
    imx6ul_device->enet_virtual_base_addr = (ENET_Type *)ueth_remap((void *)imx6ul_device->enet_phy_base_addr, UETH_REMAP, SYS_PAGE_SIZE);
    base_addr = imx6ul_device->enet_virtual_base_addr;
    config = &imx6ul_device->config;
    handle = &imx6ul_device->handle;
    buffConfig = &imx6ul_device->buffConfig;

    for (int i=0; i<GET_ARRAY_NUM(imx6ul_device->gpio); i++)
    {
        ueth_gpioinit((void *)&imx6ul_device->gpio[i], sizeof(imx6ul_device->gpio[i]));
    }
    
    IOMUXC_GPR_Type *GPR1 = (IOMUXC_GPR_Type *)ueth_remap((void *)IOMUXC_GPR, UETH_REMAP, 0x1000);
    if(imx6ul_device->mac_num == 1)
    {
        reg_value = GPR1->GPR1;
        reg_value &= ~(IOMUXC_GPR_GPR1_ENET1_CLK_SEL_MASK
                    | IOMUXC_GPR_GPR1_ENET1_CLK_SEL_MASK);
        reg_value |=  IOMUXC_GPR_GPR1_ENET1_TX_CLK_DIR(1);
        reg_value |=  IOMUXC_GPR_GPR1_ENET1_CLK_SEL(0);
        GPR1->GPR1 = reg_value;
    }
    else if(imx6ul_device->mac_num == 2)
    {
        reg_value = GPR1->GPR1;
        reg_value &= ~(IOMUXC_GPR_GPR1_ENET2_CLK_SEL_MASK
                    | IOMUXC_GPR_GPR1_ENET2_CLK_SEL_MASK);
        reg_value |=  IOMUXC_GPR_GPR1_ENET2_TX_CLK_DIR(1);
        reg_value |=  IOMUXC_GPR_GPR1_ENET2_CLK_SEL(0);
        GPR1->GPR1 = reg_value;
    } 

    // ENET_InitModuleClock();
    ueth_init_clock();
    ENET_GetDefaultConfig(config);
    config->interrupt |= (ENET_RX_INTERRUPT);
    state = enet_buffer_init(buffConfig);
    if(state != RT_EOK)
    {
        return state;
    }
    ENET_Init(base_addr, handle, config, buffConfig, imx6ul_device->dev_addr, SYS_CLOCK_HZ);
    ENET_ActiveRead(base_addr);

    // ENET_DisableInterrupts(base_addr,ENET_RX_INTERRUPT);
    // rt_hw_interrupt_install(imx6ul_device->irq_num, (rt_isr_handler_t)ENET_DriverIRQHandler, (void *)base_addr,imx6ul_device->irq_name);     
    // rt_hw_interrupt_umask(imx6ul_device->irq_num);
#ifndef POLL_INT
    ueth_hw_interrupt_install(imx6ul_device->irq_num, (void *)imx6ul_device->enet_phy_base_addr);
#endif

    return RT_EOK;
}

static rt_err_t rt_imx6ul_eth_control(rt_device_t dev, int cmd, void *args)
{
    struct rt_imx6ul_ethps *imx6ul_device = (struct rt_imx6ul_ethps *)dev;

    
    switch (cmd)
    {
    case NIOCTL_GADDR:
        /* get MAC address */
        if (args)
        {
            OCOTP_Type *ocotp_base;
            rt_uint32_t uid[2];
            rt_uint32_t uid_crc = 0;

            ocotp_base = (OCOTP_Type *)ueth_remap((void*)OCOTP_BASE, UETH_REMAP, 0x1000);

            uid[0] = ocotp_base->CFG0;
            uid[1] = ocotp_base->CFG1;

            //rt_iounmap(ocotp_base);
            ueth_remap(ocotp_base, UETH_UNMAP, 0);

            LOG_D("UNIQUE_ID is %x%x",uid[0], uid[1]);
            uid_crc = uid[0] - uid[1];
            LOG_D("UNIQUE_ID change to 32 bits %x", uid_crc);

            if (imx6ul_device->enet_phy_base_addr == ENET1)
            {
                imx6ul_device->dev_addr[0] = 0xa8;
                imx6ul_device->dev_addr[1] = 0x5e;
                imx6ul_device->dev_addr[2] = 0x45;
                imx6ul_device->dev_addr[3] = (uid_crc>>16) & 0x7f;
                imx6ul_device->dev_addr[4] = (uid_crc>>8) & 0xff;
                imx6ul_device->dev_addr[5] = uid_crc & 0xff;
            }
            else /*if (imx6ul_device->enet_phy_base_addr == ENET2)*/
            {
                imx6ul_device->dev_addr[0] = 0xa8;
                imx6ul_device->dev_addr[1] = 0x5e;
                imx6ul_device->dev_addr[2] = 0x46;
                imx6ul_device->dev_addr[3] = (uid_crc >> 16) & 0x7f;
                imx6ul_device->dev_addr[4] = (uid_crc >> 8) & 0xff;
                imx6ul_device->dev_addr[5] = uid_crc & 0xff;
            }

            memcpy(args, imx6ul_device->dev_addr, MAX_ADDR_LEN);
        }
        else
        {
            return -RT_ERROR;
        }
        break;

    default :
        break;
    }
    return RT_EOK;
}

static status_t read_data_from_eth(rt_device_t dev,void *read_data,uint16_t *read_length)
{
    status_t status = 0;
    uint16_t length = 0;
    ENET_Type *base_addr = RT_NULL;
    enet_config_t *config;
    enet_handle_t *handle;
    enet_buffer_config_t *buffConfig;
    struct rt_imx6ul_ethps *imx6ul_device = (struct rt_imx6ul_ethps *)dev;
    base_addr = imx6ul_device->enet_virtual_base_addr;
    config = &imx6ul_device->config;
    handle = &imx6ul_device->handle;
    buffConfig = &imx6ul_device->buffConfig;
    /* Get the Frame size */
    status = ENET_ReadFrame(base_addr,handle,config,read_data,&length);
    if((status == kStatus_ENET_RxFrameEmpty)||(status == kStatus_ENET_RxFrameError))
    {
        ENET_EnableInterrupts(base_addr,ENET_RX_INTERRUPT);
        if(status == kStatus_ENET_RxFrameError)
        {
            /*recv error happend reinitialize mac*/
            ENET_Init(base_addr, handle, config, buffConfig, imx6ul_device->dev_addr, SYS_CLOCK_HZ);
            ENET_ActiveRead(base_addr);
            return kStatus_ENET_RxFrameError;
        }
        else if(status == kStatus_ENET_RxFrameEmpty)
        {
            return kStatus_ENET_RxFrameEmpty;
        }
    }
    *read_length = length;
    return status;
}

#ifdef RT_USING_LWIP
/* transmit data*/
rt_err_t rt_imx6ul_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct pbuf *q = RT_NULL;
    uint16_t offset = 0;
    uint32_t last_flag = 0;
    status_t status;
    ENET_Type *base_addr = RT_NULL;
    enet_handle_t *handle;
    struct rt_imx6ul_ethps *imx6ul_device = (struct rt_imx6ul_ethps *)dev;
    base_addr = imx6ul_device->enet_virtual_base_addr;
    handle = &imx6ul_device->handle;
    RT_ASSERT(p);

    for(q = p;q != RT_NULL;q=q->next)
    {
        if(q->next == RT_NULL)
        {
            last_flag = 1;
        }
        else
        {
            last_flag = 0;
        }
        status = ENET_SendFrame(base_addr, handle, q->payload, q->len,last_flag);

        offset = offset + q->len;
        if(status == kStatus_Success)
        {
        }
        else
        {
            return RT_ERROR;
        }
    }
    if(offset > ENET_FRAME_MAX_FRAMELEN)
    {
        LOG_E("net error send length %d exceed max length",offset);
    }
    return RT_EOK;
}

struct pbuf *rt_imx6ul_eth_rx(rt_device_t dev)
{
    static struct pbuf *p_s = RT_NULL;
    struct pbuf *p = RT_NULL;
    status_t status;
    uint16_t length = 0;

    if(p_s == RT_NULL)
    {
        p_s = pbuf_alloc(PBUF_RAW, ENET_FRAME_MAX_FRAMELEN, PBUF_POOL);
        if(p_s == RT_NULL)
        {
            return RT_NULL;
        }
    }
    p = p_s;
    status = read_data_from_eth(dev,p->payload,&length);
    if(status == kStatus_ENET_RxFrameEmpty)
    {
        return RT_NULL;
    }
    else if(status == kStatus_ENET_RxFrameError)
    {
        return RT_NULL;
    }
    if(length > ENET_FRAME_MAX_FRAMELEN)
    {
        LOG_E("net error recv length %d exceed max length",length);
        return RT_NULL;
    }
    pbuf_realloc(p, length);
    p_s = RT_NULL;
    return p;
}
#endif

static rt_err_t rt_imx6ul_eth_open(rt_device_t dev, rt_uint16_t oflag)
{
    struct rt_imx6ul_ethps *imx6ul_device = (struct rt_imx6ul_ethps *)dev;
    ENET_Type *base_addr = imx6ul_device->enet_virtual_base_addr;
    ENET_EnableInterrupts(base_addr,ENET_RX_INTERRUPT);

    return RT_EOK;
}

static rt_err_t rt_imx6ul_eth_close(rt_device_t dev)
{
    struct rt_imx6ul_ethps *imx6ul_device = (struct rt_imx6ul_ethps *)dev;
    ENET_DisableInterrupts(imx6ul_device->enet_virtual_base_addr,ENET_RX_INTERRUPT);
    return RT_EOK;
}

static rt_size_t rt_imx6ul_eth_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    uint16_t length = 0;
    status_t status;
    if(!buffer) 
    {
        LOG_E("eth read invalid parameter buffer %p size %d",buffer,size);
        return 0;
    }
    status = read_data_from_eth(dev,buffer,&length);
    if((status == kStatus_ENET_RxFrameEmpty) || (status == kStatus_ENET_RxFrameError))
    {
        return 0;
    }
    return (rt_size_t)length;
}

static rt_size_t rt_imx6ul_eth_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    status_t status;
    struct rt_imx6ul_ethps *imx6ul_device = (struct rt_imx6ul_ethps *)dev;
    ENET_Type *base_addr = imx6ul_device->enet_virtual_base_addr;
    enet_handle_t *handle = &imx6ul_device->handle;

    if((!buffer) || (size > ENET_FRAME_MAX_FRAMELEN))
    {
        LOG_E("eth write invalid parameter buffer %p size %d",buffer,size);
    }
    status = ENET_SendFrame(base_addr, handle, buffer, size,1);
    if(status != kStatus_Success)
    {
        return RT_ERROR;
    }

    return RT_EOK;
}

int32_t get_instance_by_base(void *base)
{
    int32_t i = 0;
    int32_t instance = 0;
    for(i = 0; i < DEV_ENET_MAX; i ++)
    {
        if((void *)_imx6ul_eth_device[i].enet_virtual_base_addr == base)
        {
            break;
        }
    }
    if(i == DEV_ENET_MAX)
    {
        return -1;
    }
    return instance;
    
}

static void* ueth_rx_interrupt_handle(ENET_Type *base)
{
    /* Clear the transmit interrupt event. */
    base->EIR = ENET_RX_INTERRUPT;
    int32_t instance = 0;
    instance = get_instance_by_base(base);
    if(instance == -1)
    {
        LOG_E("interrput match base addr error");
        return RT_NULL;
    }
    return (void*)&(_imx6ul_eth_device[instance].parent);
}

int eth_init_done = 0;
void* ueth_rx_interrupt_detect(void) {
    ENET_Type *base = _imx6ul_eth_device[0].enet_virtual_base_addr;

#ifdef POLL_INT
    while (1)
    {
        if ((base->EIR & ENET_RX_INTERRUPT) && (base->EIMR & ENET_RX_INTERRUPT))
        {
            ENET_DisableInterrupts(base, ENET_RX_INTERRUPT);
            return ueth_rx_interrupt_handle(base);
        }
    }
#else
    ueth_int_recv();
    return ueth_rx_interrupt_handle(base);
#endif
}

/*phy link detect thread*/
static void phy_detect_thread_entry(void *param)
{
    bool link = false;
    phy_speed_t speed;
    phy_duplex_t duplex;
    ENET_Type *base_addr = RT_NULL;
    struct rt_imx6ul_ethps *imx6ul_device = (struct rt_imx6ul_ethps *)param;
    base_addr = imx6ul_device->enet_virtual_base_addr;

    phy_reset(imx6ul_device->phy_base_addr,imx6ul_device->phy_gpio_pin);
    PHY_Init(base_addr, imx6ul_device->phy_num, SYS_CLOCK_HZ,imx6ul_device->phy_id);
    PHY_GetLinkStatus(base_addr, imx6ul_device->phy_num, &link);
    if (link)
    {
        /* Get the actual PHY link speed. */
        PHY_GetLinkSpeedDuplex(base_addr, imx6ul_device->phy_num, &speed, &duplex);
        /* Change the MII speed and duplex for actual link status. */
        imx6ul_device->config.miiSpeed = (enet_mii_speed_t)speed;
        imx6ul_device->config.miiDuplex = (enet_mii_duplex_t)duplex;
    }
    else
    {
        LOG_W("PHY Link down, please check the cable connection and link partner setting.");
    }

    while(1)
    {
        PHY_GetLinkStatus(base_addr, imx6ul_device->phy_num, &link);
        if(link != imx6ul_device->phy_link_status)
        {
            if(link == true)
            {
                PHY_StartNegotiation(base_addr,imx6ul_device->phy_num);
                
            }            
            imx6ul_eth_link_change(imx6ul_device,link);
        }
        rt_thread_mdelay(DETECT_DELAY_ONE_SECOND);
    }
}

const static struct rt_device_ops _k_enet_ops =
{
    RT_NULL,
    rt_imx6ul_eth_open,
    rt_imx6ul_eth_close,
    rt_imx6ul_eth_read,
    rt_imx6ul_eth_write,
    rt_imx6ul_eth_control,
};

int imx6ul_eth_init()
{
    rt_err_t state = RT_EOK;
    char link_detect[10];
    char mac_addr[MAX_ADDR_LEN];

    if (ipc_service_init() == RT_ERROR)
    {
        return -RT_ERROR;
    }


    ueth_gpioinit((void *)&mdio_gpio[0], sizeof(mdio_gpio[0]));
    ueth_gpioinit((void *)&mdio_gpio[1], sizeof(mdio_gpio[1]));

    for (int idx=0; idx<GET_ARRAY_NUM(_imx6ul_eth_device); idx++)
    {
        _imx6ul_eth_device[idx].parent.parent.ops = &_k_enet_ops;
#ifdef RT_USING_LWIP        
        _imx6ul_eth_device[idx].parent.eth_rx     = rt_imx6ul_eth_rx;
        _imx6ul_eth_device[idx].parent.eth_tx     = rt_imx6ul_eth_tx;
#endif        
        _imx6ul_eth_device[idx].phy_link_status   = RT_FALSE;

#ifdef SAL_USING_UNET
        rt_imx6ul_eth_control((rt_device_t)(&_imx6ul_eth_device[idx]),NIOCTL_GADDR,mac_addr);
        
        rt_imx6ul_eth_init((rt_device_t)(&(_imx6ul_eth_device[idx].parent)));
#endif
        eth_init_done = 1;
        /* register eth device */
        state = eth_device_init(&(_imx6ul_eth_device[idx].parent), _imx6ul_eth_device[idx].mac_name);
        if (RT_EOK == state)
        {
            LOG_I("emac device init success");
        }
        else
        {
            LOG_E("emac device init faild: %d", state);
            state = -RT_ERROR;
        }

        rt_sprintf(link_detect,"link_d%d",_imx6ul_eth_device[idx].mac_num);
        /* start phy link detect */
        rt_thread_t phy_link_tid;
        phy_link_tid = rt_thread_create(link_detect,
                                phy_detect_thread_entry,
                                &_imx6ul_eth_device[idx],
                                4096,
                                25,
                                2);
        if (phy_link_tid != RT_NULL)
        {
            rt_thread_startup(phy_link_tid);
        }
        memset(link_detect,0,sizeof(link_detect));
    }

    return state;
}