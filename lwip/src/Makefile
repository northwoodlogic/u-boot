# SPDX-License-Identifier: GPL-2.0+

ccflags-y += -I$(src)/include

# COREFILES, CORE4FILES: The minimum set of files needed for lwIP.
obj-y += core/init.o
obj-y += core/def.o
obj-y += core/dns.o
obj-y += core/inet_chksum.o
obj-y += core/ip.o
obj-y += core/mem.o
obj-y += core/memp.o
obj-y += core/netif.o
obj-y += core/pbuf.o
obj-y += core/raw.o
obj-y += core/stats.o
obj-y += core/sys.o
obj-y += core/altcp.o
obj-y += core/altcp_alloc.o
obj-y += core/altcp_tcp.o
obj-y += core/tcp.o
obj-y += core/tcp_in.o
obj-y += core/tcp_out.o
obj-y += core/timeouts.o
obj-y += core/udp.o

# Need one or two things from the netif directory
obj-y += netif/ethernet.o

# CORE4FILES
obj-y += core/ipv4/autoip.o
obj-y += core/ipv4/dhcp.o
obj-y += core/ipv4/etharp.o
obj-y += core/ipv4/icmp.o
obj-y += core/ipv4/igmp.o
obj-y += core/ipv4/ip4_frag.o
obj-y += core/ipv4/ip4.o
obj-y += core/ipv4/ip4_addr.o

# CORE6FILES
obj-y += core/ipv6/dhcp6.o
obj-y += core/ipv6/ethip6.o
obj-y += core/ipv6/icmp6.o
obj-y += core/ipv6/inet6.o
obj-y += core/ipv6/ip6.o
obj-y += core/ipv6/ip6_addr.o
obj-y += core/ipv6/ip6_frag.o
obj-y += core/ipv6/mld6.o
obj-y += core/ipv6/nd6.o

# The porting goop to make things run on top of U-Boot
obj-y += include/arch/sys_arch.o
obj-y += include/arch/ubootif.o
