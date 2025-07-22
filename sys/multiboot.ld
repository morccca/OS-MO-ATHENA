ENTRY(_start)

SECTIONS
{
    . = 0x100000;

    .multiboot : {
        *(.multiboot)
    }

    . = ALIGN(4096);
    .text : {
        *(.text)
    }

    . = ALIGN(4096);
    .rodata : {
        *(.rodata*)
    }

    . = ALIGN(4096);
    .data : {
        *(.data)
    }

    . = ALIGN(4096);
    .bss : {
        *(COMMON)
        *(.bss)
    }

    /DISCARD/ : {
        *(.note.GNU-stack)
        *(.comment)
        *(.eh_frame)
    }
}
