#!/bin/bash

echo -n "Building loader: "
nasm -f elf -o loader.o loader.s
echo -e "done\n\n"

echo -n "Building kernel: "
gcc -o kernel.o -c kernel.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
echo -e "done\n\n"

echo -n "Building linker: "
ld -T linker.ld -o kernel.bin loader.o kernel.o
echo -e "done\n\n"

echo -n "Building floppy image: "
dd if=/dev/zero of=./pad bs=1 count=750
cat  grub-stage/stage1 grub-stage/stage2 pad kernel.bin > floppy.img
#cat  grub-stage/stage1 grub-stage/stage2 pad > floppy.img
size=`ls -l floppy.img | awk '{print $5}'`

kern_size=`ls -l kernel.bin | awk '{print $5}'`
echo "size: $kern_size"
echo "offset: `expr $kern_size / 512`"

new_size=`expr 1440000 - $size`
mv floppy.img floppy.img.tmp
dd if=/dev/zero of=./pad2 bs=1 count=$new_size
cat floppy.img.tmp pad2 > floppy.img
echo -e "done\n\n"

# use qemu to test floppy.img
qemu -fda ./floppy.img