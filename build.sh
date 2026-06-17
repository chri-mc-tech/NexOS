#!/bin/bash

mkdir -p build
cd build

rm -f *.o *.elf *.bin *.img

nasm -f bin ../bootloader/boot.asm -o boot.bin

cmake ..
make

cat boot.bin kernel.bin > os.img

kernel_size=$(wc --bytes < kernel.bin)
sectors=$(((kernel_size + 511) / 512))
echo "$kernel_size bytes, $sectors sectors needed"

qemu-system-x86_64 -drive format=raw,file=os.img