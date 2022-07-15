#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rtthread.h>
#include <channel.h>

#include <lwip/inet.h>
#include <lwip/inet_chksum.h>
#include <lwip/icmp.h>
#include <lwip/sockets.h>
#include <lwip/ip.h>

#include "srv_ping.h"

int lwip_netdev_ping(ip_addr_t *target_addr, size_t data_len,
                        uint32_t timeout, struct netdev_ping_resp *ping_resp)
{
    int s, ttl, recv_len, result = 0;
    int elapsed_time;
    rt_tick_t recv_start_tick;
    struct timeval recv_timeout = { timeout / RT_TICK_PER_SECOND, timeout % RT_TICK_PER_SECOND };

    RT_ASSERT(target_addr);
    RT_ASSERT(ping_resp);

    /* new a socket */
    if ((s = lwip_socket(AF_INET, SOCK_RAW, IP_PROTO_ICMP)) < 0)
    {
        return -RT_ERROR;
    }

    lwip_setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout));

    if (lwip_ping_send(s, target_addr, data_len) == ERR_OK)
    {
        recv_start_tick = rt_tick_get();
        if ((recv_len = lwip_ping_recv(s, &ttl)) >= 0)
        {
            elapsed_time = (rt_tick_get() - recv_start_tick) * 1000UL / RT_TICK_PER_SECOND;
            ping_resp->data_len = recv_len;
            ping_resp->ttl = ttl;
            ping_resp->ticks = elapsed_time;
            memcpy(&(ping_resp->ip_addr), target_addr, sizeof(ip_addr_t));
        }
        else
        {
            result = -RT_ETIMEOUT;
            goto __exit;
        }
    }
    else
    {
        result = -RT_ETIMEOUT;
        goto __exit;
    }

__exit:
    lwip_close(s);

    return result;
}

