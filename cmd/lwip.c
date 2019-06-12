/*
 * command wrapper around LwIP.
 * commands:
 * 	init -- send router solicitation
 * 	ndp   -- neighbor discovery protocol
 */

#include <common.h>
#include <malloc.h>
#include <command.h>
#include <memalign.h>
#include <stdlib.h>

//void lwip_init(void);
int ubcmd_run(int argc, char * const argv[]);
void ubcmd_push_packet(void *pkt, int len);

static int do_lwip(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret;
	eth_halt();
	eth_set_current();
	ret = eth_init();
	if (ret < 0) {
		eth_halt();
		return ret;
	}

	printf("%s: running lwip command\n", __func__);
	push_packet = ubcmd_push_packet;
	ret = ubcmd_run(argc, argv);
	push_packet = NULL;
	printf("%s: back into uboot\n", __func__);
	return ret;
}

U_BOOT_CMD(lwip, CONFIG_SYS_MAXARGS, 1, do_lwip,
	"Use LwIP to perform some network tasks",
	"fffffff\n"
);

