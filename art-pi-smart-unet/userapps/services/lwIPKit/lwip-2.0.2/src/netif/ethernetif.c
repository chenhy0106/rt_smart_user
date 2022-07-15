/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * COPYRIGHT (C) 2006-2018, RT-Thread Development Team
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-07-07     Bernard      fix send mail to mailbox issue.
 * 2011-07-30     mbbill       port lwIP 1.4.0 to RT-Thread
 * 2012-04-10     Bernard      add more compatible with RT-Thread.
 * 2012-11-12     Bernard      The network interface can be initialized
 *                             after lwIP initialization.
 * 2013-02-28     aozima       fixed list_tcps bug: ipaddr_ntoa isn't reentrant.
 * 2016-08-18     Bernard      port to lwIP 2.0.0
 */

#include "lwip/opt.h"

#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/netif.h"
#include "lwip/stats.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/netifapi.h"

#include "netif/etharp.h"

#include <unet.h>

#include "lwip/inet.h"

#if LWIP_IPV6
#include "lwip/ethip6.h"
#endif /* LWIP_IPV6 */

#define netifapi_netif_set_link_up(n)      netifapi_netif_common(n, netif_set_link_up, NULL)
#define netifapi_netif_set_link_down(n)    netifapi_netif_common(n, netif_set_link_down, NULL)

#ifndef RT_LWIP_ETHTHREAD_PRIORITY
#define RT_ETHERNETIF_THREAD_PREORITY   0x90
#else
#define RT_ETHERNETIF_THREAD_PREORITY   RT_LWIP_ETHTHREAD_PRIORITY
#endif

#ifndef RT_LWIP_ETHTHREAD_MBOX_SIZE
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 48
#endif

#ifndef RT_LWIP_ETHTHREAD_STACKSIZE
#define RT_LWIP_ETHTHREAD_STACKSIZE 1024
#endif

/* this function does not need,
 * use eth_system_device_init_private()
 * call by lwip_system_init().
 */
int eth_system_device_init(void)
{
    return 0;
}

void set_if(char* netif_name, char* ip_addr, char* gw_addr, char* nm_addr)
{
    ip4_addr_t *ip;
    ip4_addr_t addr;
    struct netif * netif = netif_list;

    if(strlen(netif_name) > sizeof(netif->name))
    {
        rt_kprintf("network interface name too long!\r\n");
        return;
    }

    while(netif != RT_NULL)
    {
        if(strncmp(netif_name, netif->name, sizeof(netif->name)) == 0)
            break;

        netif = netif->next;
        if( netif == RT_NULL )
        {
            rt_kprintf("network interface: %s not found!\r\n", netif_name);
            return;
        }
    }

    ip = (ip4_addr_t *)&addr;

    /* set ip address */
    if ((ip_addr != RT_NULL) && ip4addr_aton(ip_addr, &addr))
    {
        netif_set_ipaddr(netif, ip);
    }

    /* set gateway address */
    if ((gw_addr != RT_NULL) && ip4addr_aton(gw_addr, &addr))
    {
        netif_set_gw(netif, ip);
    }

    /* set netmask address */
    if ((nm_addr != RT_NULL) && ip4addr_aton(nm_addr, &addr))
    {
        netif_set_netmask(netif, ip);
    }
}

#if LWIP_DNS
#include <lwip/dns.h>
void set_dns(uint8_t dns_num, char* dns_server)
{
    ip_addr_t addr;

    if ((dns_server != RT_NULL) && ipaddr_aton(dns_server, &addr))
    {
        dns_setserver(dns_num, &addr);
    }
}
#endif

void list_if(void)
{
    rt_ubase_t index;
    struct netif * netif;

    rt_enter_critical();

    netif = netif_list;

    while( netif != RT_NULL )
    {
        rt_kprintf("network interface: %c%c%s\n",
                   netif->name[0],
                   netif->name[1],
                   (netif == netif_default)?" (Default)":"");
        rt_kprintf("MTU: %d\n", netif->mtu);
        rt_kprintf("MAC: ");
        for (index = 0; index < netif->hwaddr_len; index ++)
            rt_kprintf("%02x ", netif->hwaddr[index]);
        rt_kprintf("\nFLAGS:");
        if (netif->flags & NETIF_FLAG_UP) rt_kprintf(" UP");
        else rt_kprintf(" DOWN");
        if (netif->flags & NETIF_FLAG_LINK_UP) rt_kprintf(" LINK_UP");
        else rt_kprintf(" LINK_DOWN");
        if (netif->flags & NETIF_FLAG_ETHARP) rt_kprintf(" ETHARP");
        if (netif->flags & NETIF_FLAG_BROADCAST) rt_kprintf(" BROADCAST");
        if (netif->flags & NETIF_FLAG_IGMP) rt_kprintf(" IGMP");
        rt_kprintf("\n");
        rt_kprintf("ip address: %s\n", ipaddr_ntoa(&(netif->ip_addr)));
        rt_kprintf("gw address: %s\n", ipaddr_ntoa(&(netif->gw)));
        rt_kprintf("net mask  : %s\n", ipaddr_ntoa(&(netif->netmask)));
#if LWIP_IPV6
		{
			ip6_addr_t *addr;
			int addr_state;
			int i;

			addr = (ip6_addr_t *)&netif->ip6_addr[0];
			addr_state = netif->ip6_addr_state[0];

			rt_kprintf("\nipv6 link-local: %s state:%02X %s\n", ip6addr_ntoa(addr),
			addr_state, ip6_addr_isvalid(addr_state)?"VALID":"INVALID");

			for(i=1; i<LWIP_IPV6_NUM_ADDRESSES; i++)
			{
				addr = (ip6_addr_t *)&netif->ip6_addr[i];
				addr_state = netif->ip6_addr_state[i];

				rt_kprintf("ipv6[%d] address: %s state:%02X %s\n", i, ip6addr_ntoa(addr),
				addr_state, ip6_addr_isvalid(addr_state)?"VALID":"INVALID");
			}

		}
        rt_kprintf("\r\n");
#endif /* LWIP_IPV6 */
        netif = netif->next;
    }

#if LWIP_DNS
    {
        const ip_addr_t *ip_addr;

        for(index=0; index<DNS_MAX_SERVERS; index++)
        {
            ip_addr = dns_getserver(index);
            rt_kprintf("dns server #%d: %s\n", index, ipaddr_ntoa(ip_addr));
        }
    }
#endif /**< #if LWIP_DNS */

    rt_exit_critical();
}

#if LWIP_TCP
#include <lwip/tcp.h>
#include <lwip/priv/tcp_priv.h>

void list_tcps(void)
{
    rt_uint32_t num = 0;
    struct tcp_pcb *pcb;
    char local_ip_str[16];
    char remote_ip_str[16];

    extern struct tcp_pcb *tcp_active_pcbs;
    extern union tcp_listen_pcbs_t tcp_listen_pcbs;
    extern struct tcp_pcb *tcp_tw_pcbs;

    rt_enter_critical();
    rt_kprintf("Active PCB states:\n");
    for(pcb = tcp_active_pcbs; pcb != NULL; pcb = pcb->next)
    {
        strcpy(local_ip_str, ipaddr_ntoa(&(pcb->local_ip)));
        strcpy(remote_ip_str, ipaddr_ntoa(&(pcb->remote_ip)));

        rt_kprintf("#%d %s:%d <==> %s:%d snd_nxt 0x%08X rcv_nxt 0x%08X ",
                   num++,
                   local_ip_str,
                   pcb->local_port,
                   remote_ip_str,
                   pcb->remote_port,
                   pcb->snd_nxt,
                   pcb->rcv_nxt);
        rt_kprintf("state: %s\n", tcp_debug_state_str(pcb->state));
    }

    rt_kprintf("Listen PCB states:\n");
    num = 0;
    for(pcb = (struct tcp_pcb *)tcp_listen_pcbs.pcbs; pcb != NULL; pcb = pcb->next)
    {
        rt_kprintf("#%d local port %d ", num++, pcb->local_port);
        rt_kprintf("state: %s\n", tcp_debug_state_str(pcb->state));
    }

    rt_kprintf("TIME-WAIT PCB states:\n");
    num = 0;
    for(pcb = tcp_tw_pcbs; pcb != NULL; pcb = pcb->next)
    {
        strcpy(local_ip_str, ipaddr_ntoa(&(pcb->local_ip)));
        strcpy(remote_ip_str, ipaddr_ntoa(&(pcb->remote_ip)));

        rt_kprintf("#%d %s:%d <==> %s:%d snd_nxt 0x%08X rcv_nxt 0x%08X ",
                   num++,
                   local_ip_str,
                   pcb->local_port,
                   remote_ip_str,
                   pcb->remote_port,
                   pcb->snd_nxt,
                   pcb->rcv_nxt);
        rt_kprintf("state: %s\n", tcp_debug_state_str(pcb->state));
    }
    rt_exit_critical();
}
#endif /* LWIP_TCP */

#if LWIP_UDP
#include "lwip/udp.h"
void list_udps(void)
{
    struct udp_pcb *pcb;
    rt_uint32_t num = 0;
    char local_ip_str[16];
    char remote_ip_str[16];

    rt_enter_critical();
    rt_kprintf("Active UDP PCB states:\n");
    for (pcb = udp_pcbs; pcb != NULL; pcb = pcb->next)
    {
        strcpy(local_ip_str, ipaddr_ntoa(&(pcb->local_ip)));
        strcpy(remote_ip_str, ipaddr_ntoa(&(pcb->remote_ip)));

        rt_kprintf("#%d %d %s:%d <==> %s:%d \n",
                   num, (int)pcb->flags,
                   local_ip_str,
                   pcb->local_port,
                   remote_ip_str,
                   pcb->remote_port);

        num++;
    }
    rt_exit_critical();
}
#endif /* LWIP_UDP */
