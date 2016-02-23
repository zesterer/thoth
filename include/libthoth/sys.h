#ifndef THOTH_SYS_H
#define THOTH_SYS_H

#include "types.h"

namespace thoth
{
	static inline void outb(uint16 port, uint8 value)
	{
		asm volatile("outb %0, %1" : : "a"(value), "Nd"(port));
		/* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
		* Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
		* The  outb  %al, %dx  encoding is the only option for all other cases.
		* %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
	}
	
	static inline void outw(uint16 port, uint16 value)
	{
		asm volatile("outw %0, %1" : : "a"(value), "Nd"(port));
		/* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
		* Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
		* The  outb  %al, %dx  encoding is the only option for all other cases.
		* %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
	}
	
	static inline void outl(uint16 port, uint32 value)
	{
		asm volatile("outl %0, %1" : : "a"(value), "Nd"(port));
		/* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
		* Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
		* The  outb  %al, %dx  encoding is the only option for all other cases.
		* %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
	}
	
	static inline uint8 inb(uint16 port)
	{
		uint8 result;
		asm volatile("inb %[port], %[ret]" : [ret] "=a"(result) : [port] "Nd"(port));
		return result;
	}
	
	static inline uint16 inw(uint16 port)
	{
		uint16 result;
		asm volatile("inw %[port], %[ret]" : [ret] "=a"(result) : [port] "Nd"(port));
		return result;
	}
	
	static inline uint32 inl(uint16 port)
	{
		uint32 result;
		asm volatile("inl %[port], %[ret]" : [ret] "=a"(result) : [port] "Nd"(port));
		return result;
	}
	
	static inline bool getInterruptsEnabled()
	{
		uint64 ret;
		asm volatile ("rdtsc" : "=A"(ret));
		return ret;
	}
	
	static inline uint64 readCPUTimestampCounter()
	{
		unsigned long flags;
		asm volatile("pushf\npop %0" : "=g"(flags));
		return flags & (1 << 9);
	}
}

#endif
