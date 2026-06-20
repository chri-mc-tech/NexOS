[org 0x7c00]
BITS 16

cli
xor ax, ax
mov ss, ax
mov es, ax
mov ds, ax
mov sp, 0x7c00
sti

mov ax, 0x0003
int 0x10

mov si, start_message
call print

mov [BOOT_DRIVE], dl
mov bx, 0x1000
mov ah, 0x02

; da cambiare in base a dimensione kernel
mov al, 3

mov ch, 0
mov cl, 2
mov dh, 0
mov dl, [BOOT_DRIVE]
int 0x13

jc disk_error

cli
lgdt [gdt_descriptor]
mov eax, cr0
or eax, 1
mov cr0, eax
jmp 08h:init_pm

[bits 32]
init_pm:
    mov ax, 0x10
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov esp, 0x90000
    jmp 0x1000

[bits 16]
print:
  mov ah, 0Eh
.run:
  lodsb
  cmp al, 0
  je .done
  int 10h
  jmp .run
.done:
  ret

start_message db '[bootloader] NexOS Bootloader Started', 0x0D, 0x0A, '[bootloader] Loading Kernel...', 0

gdt_start:
    dq 0x0

gdt_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0x9A
    db 0xCF
    db 0x00

gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 0x92
    db 0xCF
    db 0x00

gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

BOOT_DRIVE db 0

disk_error:
    mov si, error_msg
    call print
    jmp $

error_msg db '[bootloader] DISK ERROR: Kernel not found!', 0

times 510 - ($-$$) db 0
dw 0xAA55