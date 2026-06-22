#!/bin/bash

mkdir -p build
cd build

rm -f *.o *.elf *.bin *.img

cmake ..
make

kernel_size=$(wc --bytes < kernel.bin)
sectors=$(((kernel_size + 511) / 512))
echo "$kernel_size bytes, $sectors sectors needed"

nasm -f bin ../bootloader/boot.asm -D KERNEL_SECTORS=$sectors -o boot.bin

cat boot.bin kernel.bin > os.img

qemu-system-x86_64 -drive format=raw,file=os.img