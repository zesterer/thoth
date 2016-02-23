#!/bin/sh

ISO=`ls -t isobuild/thoth*.iso | head -n1`

qemu-system-x86_64 -cdrom $ISO
