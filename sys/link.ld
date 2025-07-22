ENTRY(_start)

SECTIONS
{
    . = 0x100000;

    .multiboot ALIGN(4K) : AT(ADDR(.multiboot))
    {
        *(.multiboot)
    }

    .text ALIGN(4K) : AT(ADDR(.text))
    {
        *(.text)
    }

    .rodata ALIGN(4K) : AT(ADDR(.rodata))
    {
        *(.rodata)
        *(.rdata)
    }

    .data ALIGN(4K) : AT(ADDR(.data))
    {
        *(.data)
        *(.ctors)
    }

    .bss ALIGN(4K) : AT(ADDR(.bss))
    {
        *(COMMON)
        *(.bss)
    }

    /DISCARD/ :
    {
        *(.reloc)
        *(.comment)
        *(.note)
    }
}
