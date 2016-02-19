#Thoth

A modular, micro-kernel operating system for the future

## Building

Make sure you have an "i386-elf" build target version of gcc and binutils installed in a system-accessible location.

Thoth uses the SCons build system. To compile the kernel, simply run scons in the root of the repository.

`scons`

## Running

To run the compile kernel without a bootloader using QEMU, simply run the utility script provided

`sh run-kernel-qemu.sh`

## Creating an ISO

Make sure you have the necessary grub tools installed.

`sh create-iso.sh`

Run the iso with:

`sh run-iso-qemu.sh`
