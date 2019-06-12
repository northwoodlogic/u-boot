
/*
 * This also includes the U-Boot Ethernet rx/tx API to LwIP NIC driver.
 *
 * There is a macro collision from uboot flash.h and lwip so be careful about
 * not getting the U-Boot/LwIP streams crossed.
 *
 * http://www.nongnu.org/lwip/2_0_x/group__lwip__nosys.html
 * https://lwip.fandom.com/wiki/Porting_For_Bare_Metal
 * https://github.com/ARMmbed/lwip/blob/master/src/netif/ethernetif.c
 * https://lwip.fandom.com/wiki/Writing_a_device_driver
 * https://github.com/yonch/lwip-example/blob/master/mch_main.c
 */

#include "lwip/opt.h"

#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/snmp.h"
#include "lwip/ethip6.h"
#include "lwip/etharp.h"

struct ubif_priv {
	int foo;
};

// This does the actual output onto the network interface
static err_t
ubif_linkoutput(struct netif *netif, struct pbuf *p)
{
	printf("linkout called..\n");

		return ERR_OK;
}

err_t
ubif_init(struct netif *netif)
{
	struct ubif_priv *priv;
  	priv = (struct ubif_priv *)mem_malloc(sizeof(struct ubif_priv));
  	if (!priv)
		return ERR_MEM;

	netif->name[0] = 'u';
	netif->name[1] = 'b';

	netif->mtu = 1500;
	netif->state = priv;

	netif->output = etharp_output;
	netif->output_ip6 = ethip6_output;
	netif->linkoutput = ubif_linkoutput;

	// I think I need to set
	netif->flags = 0;
	netif->flags |= NETIF_FLAG_BROADCAST;
	netif->flags |= NETIF_FLAG_ETHARP;
	netif->flags |= NETIF_FLAG_ETHERNET;
	netif->flags |= NETIF_FLAG_IGMP;
	netif->flags |= NETIF_FLAG_MLD6;
	MIB2_INIT_NETIF(netif, snmp_ifType_ethernet_csmacd, 100000000);

	//
	// and when the link comes up set
	// netif->flags |= NETIF_FLAG_LINK_UP;
	//
	netif->hwaddr[0] = 0xb8;
	netif->hwaddr[1] = 0x27;
	netif->hwaddr[2] = 0xeb;
	netif->hwaddr[3] = 0x70;
	netif->hwaddr[4] = 0xdb;
	netif->hwaddr[5] = 0xea;

///	  SMEMCPY(netif->hwaddr, your_mac_address_goes_here, sizeof(netif->hwaddr));
	netif->hwaddr_len = sizeof(netif->hwaddr);


	return ERR_OK;
}

//static void ubif_status_callback(struct netif *netif) {
//	printf("%s: netif status changed\n", __func__);
//}



// main entry point from U-Boot into lwip. This should probably go in a different file...
//
#include <lwip/init.h>
#include <lwip/sys.h>
#include <lwip/timeouts.h>

void ubcmd_eth_poll(void);

int
ubcmd_run(int argc, char * const argv[])
{
	static int ubc_once = 0;
	static struct netif netif;
	memset(&netif, 0, sizeof(struct netif));

	if (ubc_once == 0) {
		lwip_init();
// the compiler complains about the IP4_ADDR_ANY values but when IP6 & IP4 are both
// defined it's a union type that works.
		netif_add(&netif, IP4_ADDR_ANY, IP4_ADDR_ANY, IP4_ADDR_ANY, NULL, ubif_init, netif_input);
		netif_create_ip6_linklocal_address(&netif, 1);
		netif.ip6_autoconfig_enabled=1;
// netif status callback is not defined in our lwipopts
//		netif_set_status_callback(&netif, ubif_status_callback);
		netif_set_default(&netif);
		netif_set_up(&netif);

		ubc_once = 1;
	}

	netif_set_link_up(&netif);
	uint32_t start_time = sys_now();
	printf("%s: lwip start time: %d\n", __func__, (int)start_time);
	while (sys_now() < (start_time + (1000 * 30))) {

		ubcmd_eth_poll();
		sys_check_timeouts();
	}
	printf("%s: lwip ending\n", __func__);
	netif_set_link_down(&netif);
	return 0;
}

// drivers call this which in turns calls a "push_packet" callback function if set. find out how to
// set that and make it push packets into lwip
//
// The RPI USB Ethernet driver is smsc95xx.c
//
//dave@linux-rvpn:~/github/u-boot> grep -r "net_process_received_packet" .

void
ubcmd_push_packet(void *pkt, int len)
{
	printf("got a packet of %d bytes\n", len);
}

// this is in u-boot
void eth_rx(void);

void
ubcmd_eth_poll(void)
{
	eth_rx();
}
