#ifndef KERNEL_GDT_H
#define KERNEL_GDT_H

#include "thoth/types.h"

#define GDTBASE 0x00000800

/*
struct GDTDescriptor
{
	uint16 limit;
	uint32 base;
} __attribute__((packed));
*/

struct GDTDescriptor
{
	uint16 lim0_15;
	uint16 base0_15;
	uint8 base16_23;
	uint8 access;
	uint8 lim16_19 : 4;
	uint8 other : 4;
	uint8 base24_31;
}__attribute__((packed));

void initGDTDescriptor(uint32 base, uint32 limit, uint8 access, uint8 other, struct GDTDescriptor* descriptor)
{
	descriptor->lim0_15   = (limit & 0x0000FFFF);
	descriptor->base0_15  = (base &  0x0000FFFF);
	descriptor->base16_23 = (base &  0x00FF0000) >> 16;
	descriptor->access = access;
	descriptor->lim16_19  = (limit & 0x000F0000) >> 16;
	descriptor->other = (other & 0x0F);
	descriptor->base24_31 = (base &  0xFF000000) >> 24;
}

void initGDT()
{
	default_tss.debug_flag = 0x00;
    default_tss.io_map = 0x00;
    default_tss.esp0 = 0x1FFF0;
    default_tss.ss0 = 0x18;

    /* initialize gdt segments */
    initGDTDescriptor(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
    initGDTDescriptor(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);  /* code */
    initGDTDescriptor(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);  /* data */
    initGDTDescriptor(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);      /* stack */

    initGDTDescriptor(0x0, 0xFFFFF, 0xFF, 0x0D, &kgdt[4]);  /* ucode */
    initGDTDescriptor(0x0, 0xFFFFF, 0xF3, 0x0D, &kgdt[5]);  /* udata */
    initGDTDescriptor(0x0, 0x0, 0xF7, 0x0D, &kgdt[6]);      /* ustack */

    initGDTDescriptor((uint32) & default_tss, 0x67, 0xE9, 0x00, &kgdt[7]); /* descripteur de tss */

    /* initialize the gdtr structure */
    kgdtr.limite = GDTSIZE * 8;
    kgdtr.base = GDTBASE;

    /* copy the gdtr to its memory area */
    memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite);

    /* load the gdtr registry */
    asm("lgdtl (kgdtr)");

    /* initiliaz the segments */
    asm("   movw $0x10, %ax \n \
            movw %ax, %ds   \n \
            movw %ax, %es   \n \
            movw %ax, %fs   \n \
            movw %ax, %gs   \n \
            ljmp $0x08, $next   \n \
            next:       \n");
}

#endif
