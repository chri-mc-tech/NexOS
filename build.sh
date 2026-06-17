#!/bin/bash

mkdir -p build
cd build

rm -f *.o *.elf *.bin *.img

nasm -f bin ../bootloader/boot.asm -o boot.bin

cmake ..
make

cat boot.bin kernel.bin > os.img

qemu-system-x86_64 -drive format=raw,file=os.img