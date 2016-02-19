#ifndef THOTH_SYS_H
#define THOTH_SYS_H

#include "types.h"

namespace thoth
{
	static inline void outb(uint16 port, uint16 value)
	{
		asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
		/* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
		* Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
		* The  outb  %al, %dx  encoding is the only option for all other cases.
		* %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
	}
}

#endif
