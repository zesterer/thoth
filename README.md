# Thoth

A modular, x86_64 micro-kernel operating system for the future

![alt tag](https://raw.githubusercontent.com/zesterer/thoth/master/misc/screen-2016-02-23.png "A screenshot of Thoth's state as of 2016-02-23")

A screenshot of Thoth running on the QEMU virtual machine

## About Thoth

Thoth is a hobby OS I decided to begin work on as a break from other projects. The kernel is written in a mixture of C++ and AT&T assembly.

Included with the operating system is a compatible C standard library (hopefully future releases will see this library mature into a user-space library too).

Thoth aims to be POSIX-compliant (it's a long way from that yet given that it still lacks both a filesystem and a user-space) but is not intended to be a run-of-the-mill UNIX clone. POSIX compliance is an 'extra' on top of everything else.

## Building

Make sure you have an "x86_64-elf" build target version of gcc and binutils installed in a system-accessible location.

Thoth uses the SCons build system. To compile the kernel, simply run scons in the root of the repository.

`scons`

## Running

To run the compile kernel without a bootloader using QEMU, simply run the utility script provided

`sh kernel-run-qemu.sh`

## Creating an ISO

Make sure you have the necessary grub tools installed.

`sh create-iso.sh`

Run the iso with:

`sh iso-run-qemu.sh`

Alternatively, a script exists to run both of the above commands at once.

`sh test.sh`

## Credit

All of the helpful people who reside usually within the #osdev channel on Freenode.
