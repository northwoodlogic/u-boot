// This link has been very useful:
// https://lwip.fandom.com/wiki/Porting_For_Bare_Metal

#ifndef LWIP_CONFIG_ARCH_H
#define LWIP_CONFIG_ARCH_H

// From U-Boot
#include <compiler.h>
#include <stdio.h>
#include <stdlib.h>

// The code that comes with U-Boot isn't 100% complete with respect to
// the c lib support. Some stuff is implemneted in sys_arch.c
int atoi(const char *nptr);
// long simple_strtol(const char *cp, char **endp, unsigned int base);


#define LWIP_NO_UNISTD_H	1
#define LWIP_NO_STDINT_H	1
#define LWIP_NO_STDDEF_H	1
#define LWIP_NO_LIMITS_H	1
#define LWIP_NO_CTYPE_H		1

typedef uint8_t   u8_t;
typedef int8_t    s8_t;
typedef uint16_t  u16_t;
typedef int16_t   s16_t;
typedef uint32_t  u32_t;
typedef int32_t   s32_t;

#if LWIP_HAVE_INT64
typedef uint64_t  u64_t;
typedef int64_t   s64_t;
#endif
typedef uintptr_t mem_ptr_t;

/* Compiler hints for packing structures */
#define PACK_STRUCT_FIELD(x)    x
#define PACK_STRUCT_STRUCT  __attribute__((packed))
#define PACK_STRUCT_BEGIN
#define PACK_STRUCT_END

/* Plaform specific diagnostic output */
#define LWIP_PLATFORM_DIAG(x)   do {    \
        printf x;			\
    } while (0)

#define LWIP_PLATFORM_ASSERT(x) do {				\
        printf("Assert \"%s\" failed at line %d in %s\n",	\
                x, __LINE__, __FILE__);				\
    } while (0)

// TODO: figure out how to abort u-boot and place that call after the printf in the assert macro above
//        mch_abort();
//
#endif
