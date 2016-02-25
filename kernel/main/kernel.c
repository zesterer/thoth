/*
* This file is part of Thoth.
* 
* Copyright (C) 2016  Joshua Barretto <joshua.s.barretto@gmail.com>
* 
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

/*
* Name:         kernel.c
* 
* Description:  Part of Thoth's kernel
* 
* Notes:        NONE
*/

// Local
#include "kernel.h"

// libthoth
#include "libthoth/type.h"
#include "libthoth/dmm/dmm.h"

// libkernel
#include "libkernel/vga/vga.h"
#include "libkernel/vga/vgastream.h"

// libc
#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/assert.h"

//static char* thoth_logo = (char*)"          ________         _____ _           _   _         _____/ o  \\   \\_      |_   _| |__   ___ | |_| |__     / ____     |     \\       | | | '_ \\ / _ \\| __| '_ \\   //     \\    /      |      | | | | | | (_) | |_| | | |  '       )__(______/       |_| |_| |_|\\___/ \\__|_| |_|";

//static char* thoth_logo = (char*)"##################...######...#...####........###..##.....###.####...####.###....#######....########.....######.........###.........####........";

//A pointer to the end of the kernel
extern void* _end_of_kernel asm("_end_of_kernel");

void kernel_init()
{
	assert_test(true, "Set up temporary stack");
	assert_test(true, "Init GDT and paging tables");
	assert_test(true, "Switch to 64-bit long mode");
	assert_test(true, "Init stable environment");
	assert_test(true, "Jump to kernel entry location");
	assert_test(true, "Init text-mode VGA buffer");
	//assert_test(thoth::getInterruptsEnabled(), "Test interrupts enabled");
	
	bool enabled_dmm = dmm_set(&_end_of_kernel, 0x4000000) == 0;
	assert_test(enabled_dmm, "Set up kernel-space DMM");
	
	kernel_run();
}

void kernel_run()
{
	//thoth::vgaDrawTextIcon(thoth_logo, 12, 12);
	puts("\n");
	printf("\\B3\\CFWelcome to the \\C8Thoth\\CF operating system\\B0\\CF\n");
	char version[6] = "X.Y.Z";
	version[0] = '0' + VERSION_MAJOR;
	version[2] = '0' + VERSION_MINOR;
	version[4] = '0' + VERSION_RELEASE;
	printf("Version \\C4");
	printf(version);
	printf("\\CF\n");
	
	printf("%c Hello! I'm %d testing %s printf %x %X output %u .\n", '!', 1378, "the", 0xDEAD, 0xBEEF, -13);
}
