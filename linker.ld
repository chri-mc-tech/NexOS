ENTRY(_start)
SECTIONS {
    . = 0x1000;
    .boot : { *(.boot) }
    .text : { *(.text) }
    .data : { *(.data) }
    .bss  : { *(.bss)  }
}