ENTRY(kernel_main)

SECTIONS {
    . = 0x100000;

    .text : {
        *(.multiboot)
        *(.text*)
    }

    .rodata : { *(.rodata*) }
    .data : { *(.data*) }
    .bss : {
        *(.bss*)
        *(COMMON)
    }

    /DISCARD/ : { *(.eh_frame) *(.note.GNU-stack) }
}
