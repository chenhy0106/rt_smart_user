#ifndef SRV_PING_H__
#define SRV_PING_H__

#include <lwip/ip.h>

/* The network interface device ping response object */
struct netdev_ping_resp
{
    ip_addr_t ip_addr;                           /* response IP address */
    uint16_t data_len;                           /* response data length */
    uint16_t ttl;                                /* time to live */
    uint32_t ticks;                              /* response time, unit tick */
    void *user_data;                             /* user-specific data */
};

extern int lwip_ping_recv(int s, int *ttl);
extern err_t lwip_ping_send(int s, ip_addr_t *addr, int size);

int lwip_netdev_ping(ip_addr_t *target_addr, size_t data_len,
    uint32_t timeout, struct netdev_ping_resp *ping_resp);

#endif
