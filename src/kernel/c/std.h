#ifndef KERNEL_C_STD_H
#define KERNEL_C_STD_H

//----STANDARD----
#include "stddef.h"
#include "stdint.h"

/* Vendor-strings. */
#define CPUID_VENDOR_OLDAMD       "AMDisbetter!" //early engineering samples of AMD K5 processor
#define CPUID_VENDOR_AMD          "AuthenticAMD"
#define CPUID_VENDOR_INTEL        "GenuineIntel"
#define CPUID_VENDOR_VIA          "CentaurHauls"
#define CPUID_VENDOR_OLDTRANSMETA "TransmetaCPU"
#define CPUID_VENDOR_TRANSMETA    "GenuineTMx86"
#define CPUID_VENDOR_CYRIX        "CyrixInstead"
#define CPUID_VENDOR_CENTAUR      "CentaurHauls"
#define CPUID_VENDOR_NEXGEN       "NexGenDriven"
#define CPUID_VENDOR_UMC          "UMC UMC UMC "
#define CPUID_VENDOR_SIS          "SiS SiS SiS "
#define CPUID_VENDOR_NSC          "Geode by NSC"
#define CPUID_VENDOR_RISE         "RiseRiseRise"

namespace SquidOS
{
	namespace Kernel
	{
		namespace C
		{
			static char lastCharacter = 0;
			
			extern char int_to_char(uint8_t v);

			extern size_t strlen(const char* str);
			
			extern void wait(uint32_t time);
			
			extern uint8_t inb(uint16_t port);
			
			extern void outb(uint16_t port, uint8_t val);
			
			extern char getScancode();
			
			extern char scancodeToCharacter(char c);
			
			extern bool areInterruptsEnabled();
			
			extern void cpuid(int code, uint32_t* a, uint32_t* d);
			
			extern void lidt(void* base, uint16_t size);
		}
	}
}

#endif
