#include <stdio.h>
#include <drv_eth.h>

int main() {
    struct rt_imx6ul_ethps * eth = RT_NULL;
    rt_err_t init_state = imx6ul_eth_init(0, &eth);
    if (init_state == RT_EOK) 
    {
        printf("enet init OK\n");
    }
    else
    {
        printf("enet init fail\n");
    }
    

    while (1)
    {
        uint32_t interrupt = ENET_GetInterruptStatus(eth->enet_virtual_base_addr);
        if (interrupt)
        {
            printf("get interrupt %x\n", interrupt);
            ENET_ClearInterruptStatus(eth->enet_virtual_base_addr, interrupt);
        }

        rt_thread_mdelay(500);
    }
}

