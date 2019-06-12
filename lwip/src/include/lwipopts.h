#ifndef LWIP_OPTS_H
#define LWIP_OPTS_H

#define NO_SYS 1

// Sockets API won't work without threads.
#define LWIP_SOCKET 0
#define LWIP_NETCONN 0

// May want to look into these
// #define MEM_LIBC_MALLOC 1
// #define MEMP_MEM_MALLOC 1
// #define MEMP_MEM_INIT 1
#define MEM_ALIGNMENT 4

// U-Boot gives these to us.
#define LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS 1

// We've only got one thread and one context
#define SYS_LIGHTWEIGHT_PROT 0

// Dual stack
#define LWIP_IPV4 1
#define LWIP_IPV6 1

#endif
