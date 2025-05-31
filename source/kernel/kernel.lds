SECTIONS {
    . = 0x10000;

    .text : {
        *(.text)
    }

    .rodata : {
        *(.rodata)
    }

    . = 0x20000;

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}