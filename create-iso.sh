#!/bin/sh

DATE=`date --date="now" "+%Y-%m-%d"`

mkdir -p isobuild/isodir/boot/grub
cp src/thoth.bin isobuild/isodir/boot/thoth.bin
cp grub.cfg isobuild/isodir/boot/grub/grub.cfg
grub2-mkrescue -o isobuild/thoth-${DATE}.iso isobuild/isodir
echo "Created Thoth ISO"
