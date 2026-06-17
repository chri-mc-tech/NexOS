cmake_minimum_required(VERSION 3.20)
project(NexOS NONE)

add_custom_command(
        OUTPUT kernel_entry.o
        COMMAND nasm -f elf32 ${CMAKE_SOURCE_DIR}/kernel/kernel_entry.asm -o kernel_entry.o
)

add_custom_command(
        OUTPUT kernel.o
        COMMAND gcc -m32 -ffreestanding -fno-pie -fno-exceptions -fno-rtti -nostdlib -c ${CMAKE_SOURCE_DIR}/kernel/kernel.cpp -o kernel.o
)

add_custom_command(
        OUTPUT kernel.elf
        COMMAND ld -m elf_i386 -T ${CMAKE_SOURCE_DIR}/linker.ld -o kernel.elf kernel_entry.o kernel.o
        DEPENDS kernel_entry.o kernel.o
)

add_custom_command(
        OUTPUT kernel.bin
        COMMAND objcopy -O binary kernel.elf kernel.bin
        DEPENDS kernel.elf
)

add_custom_target(kernel ALL DEPENDS kernel.bin)