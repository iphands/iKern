#!/bin/bash

function fail_exit {
    if [ $? -ne 0 ]
    then
	exit 1
    fi
}

echo -n "Building loader: "
nasm -f elf -o loader.o loader.s
fail_exit
echo -e "done\n\n"

echo -n "Building kernel: "
gcc -m32 -std=gnu99 -o kernel.o -c kernel.c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
fail_exit
echo -e "done\n\n"

echo -n "Building linker: "
ld -T linker.ld -o kernel.bin loader.o kernel.o 2>/dev/null || ld -T linker.ld -o kernel.bin loader.o kernel.o -m elf_i386
fail_exit
echo -e "done\n\n"

echo -n "Building floppy image: "
if [ ! -f pad ]
then
    dd if=/dev/zero of=./pad bs=1 count=750
fi

fail_exit

cat  grub-stage/stage1 grub-stage/stage2 pad kernel.bin > floppy.img
fail_exit

#cat  grub-stage/stage1 grub-stage/stage2 pad > floppy.img
size=`ls -l floppy.img | awk '{print $5}'`
kern_size=`ls -l kernel.bin | awk '{print $5}'`
new_size=`expr 1440000 - $size`
#mv floppy.img floppy.img.tmp
# dd if=/dev/zero of=./pad2 bs=1 count=$new_size
#cat floppy.img.tmp pad2 > floppy.img
echo -e "done\n\n"

echo "size: $kern_size"
echo "offset: `expr $kern_size / 512`"

# use qemu to test floppy.img
qemu -kernel kernel.bin
#qemu -fda ./floppy.img
