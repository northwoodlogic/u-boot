/* U-Boot env doesn't have an atoi function. LWIP needs that, write one here */
#include "cc.h"
#include <common.h>
#include <exports.h>

uint32_t sys_now(void) {
	/* According to U-Boot lib/KConfig CONFIG_SYS_HZ should always be 1000 */
	return (uint32_t)(get_timer(0) * (1000 / CONFIG_SYS_HZ));
}

int atoi(const char *nptr) {
	return (int)simple_strtol(nptr, NULL, 10);
}


