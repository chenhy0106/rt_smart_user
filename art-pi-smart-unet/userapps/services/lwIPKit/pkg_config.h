#ifndef PKG_CONFIG_H__
#define PKG_CONFIG_H__

// #define POLL_INT

// #define LWIP_DEBUG
// #define RT_LWIP_ICMP_DEBUG
// #define RT_LWIP_IP_DEBUG
// #define RT_LWIP_UDP_DEBUG
// #define RT_LWIP_DHCP_DEBUG
// #define RT_LWIP_NETIF_DEBUG
// #define RT_LWIP_ETHARP_DEBUG
// #define RT_LWIP_DNS_DEBUG
// #define RT_LWIP_PBUF_DEBUG
// #define RT_LWIP_MEMP_DEBUG
// #define RT_LWIP_SOCKETS_DEBUG

#define LWIPKIT
#define RT_USING_LWIP
#define RT_USING_LWIP202
#define RT_LWIP_IGMP
#define RT_LWIP_ICMP
#define RT_LWIP_DNS
#define RT_LWIP_DHCP
#define IP_SOF_BROADCAST 1
#define IP_SOF_BROADCAST_RECV 1

#define RT_LWIP_IPADDR "10.0.2.15"
#define RT_LWIP_GWADDR "10.0.2.2"
#define RT_LWIP_MSKADDR "255.255.255.0"
#define RT_LWIP_UDP
#define RT_LWIP_TCP
#define RT_LWIP_RAW
#define RT_MEMP_NUM_NETCONN 8
#define RT_LWIP_PBUF_NUM 2048 // the number of buffers in the pbuf pool.

#define RT_LWIP_PBUF_STRUCT_NUM        2048 // the number of memp struct pbufs. If the application
                                            // sends a lot of data out of ROM (or other static memory), this
                                            // should be set high.
#define RT_LWIP_NETBUF_NUM             2048 // the number of struct netbufs.

// the number of struct tcpip_msg, which is used
// for sequential API communication and incoming packets. 
#define RT_MEMP_NUM_TCPIP_MSG_API      2048
#define RT_MEMP_NUM_TCPIP_MSG_INPKT    2048

#define RT_TCP_RECVMBOX_SIZE   16384 //  The mailbox size for the incoming packets on a NETCONN_TCP.
#define RT_UDP_RECVMBOX_SIZE   1024
#define RT_RECV_BUFSIZE_DEFAULT            2048 // maximum amount of bytes queued in recvmbox
                                                // not used for TCP: adjust TCP_WND instead

#define RT_LWIP_RAW_PCB_NUM 4
#define RT_LWIP_UDP_PCB_NUM 8
#define RT_LWIP_TCP_PCB_NUM 8
#define RT_LWIP_TCP_SEG_NUM 8192  // the number of simultaneously queued TCP segments.
#define RT_LWIP_TCP_SND_BUF 8192 // TCP sender buffer space (bytes).
#define RT_LWIP_TCP_WND 65535
#define RT_LWIP_TCPTHREAD_PRIORITY 25
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 256
#define RT_LWIP_TCPTHREAD_STACKSIZE 8192
// #define LWIP_NO_RX_THREAD
// #define LWIP_NO_TX_THREAD
#define RT_LWIP_ETHTHREAD_PRIORITY 12
#define RT_LWIP_ETHTHREAD_STACKSIZE 8192
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 256
#define RT_LWIP_REASSEMBLY_FRAG
#define LWIP_NETIF_STATUS_CALLBACK 1
#define LWIP_NETIF_LINK_CALLBACK 1
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
#define RT_LWIP_NETIF_LOOPBACK
#define LWIP_NETIF_LOOPBACK 1
#define RT_LWIP_STATS
#define RT_LWIP_USING_PING

#define RT_USING_ENET1
#define FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL 1

#define NETDEV_IPV4 1

#endif
