#ifndef LWIPOPTS_H
#define LWIPOPTS_H

// Basic lwIP configuration for Pico W
#define LWIP_SOCKET           1
#define LWIP_NETCONN          0
#define LWIP_TIMEVAL_PRIVATE  0
#define MEM_ALIGNMENT         4
#define MEM_SIZE             4000
#define MEMP_NUM_PBUF         8
#define MEMP_NUM_NETBUF       4
#define LWIP_ARP              1
#define LWIP_ICMP             1
#define LWIP_UDP              1
#define LWIP_TCP              1
#define TCP_WND             2048
#define TCP_MSS              536

#endif // LWIPOPTS_H