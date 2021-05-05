#!/bin/bash
set -e

mkdir -p build

echo -n "Building loader: "
nasm -f elf32 -o ./build/loader.o ./src/loader.s
echo -e "done"

echo -n "Building kernel: "
gcc -Os -Wall -Wextra -march=core2 -m32 -fno-pie -ffreestanding -c ./src/kernel.c -o ./build/kernel.o
echo -e "done"

echo -n "Linking:         "
ld -m elf_i386 -Ttext 0x1000 -o ./build/kernel.bin ./build/loader.o ./build/kernel.o
echo -e "done"

kern_size=`ls -l ./build/kernel.o | awk '{print $5}'`
echo "Kernel size:     $kern_size"
