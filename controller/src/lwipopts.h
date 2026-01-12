#ifndef LWIPOPTS_H
#define LWIPOPTS_H

#define NO_SYS                 0
#define SYS_LIGHTWEIGHT_PROT   1

#define LWIP_NETCONN           1
#define LWIP_SOCKET            0

#define LWIP_DHCP              1
#define LWIP_AUTOIP            0

#define MEM_ALIGNMENT          4
#define MEM_SIZE               (32 * 1024)

#define MEMP_NUM_PBUF          16
#define MEMP_NUM_NETBUF        8

#define LWIP_ARP               1
#define LWIP_ICMP              1
#define LWIP_UDP               1
#define LWIP_TCP               1

#define TCP_WND                2048
#define TCP_MSS                536

#define LWIP_NETIF_HOSTNAME    1
#define LWIP_NETIF_API         1

#endif
