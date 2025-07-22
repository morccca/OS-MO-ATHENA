[BITS 32]

; Multiboot constants
MULTIBOOT_MAGIC         equ 0x1BADB002
MULTIBOOT_ALIGN         equ 1 << 0
MULTIBOOT_MEMINFO       equ 1 << 1
MULTIBOOT_FLAGS         equ MULTIBOOT_ALIGN | MULTIBOOT_MEMINFO
MULTIBOOT_CHECKSUM      equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

section .multiboot
align 4
multiboot_header:
    dd MULTIBOOT_MAGIC
    dd MULTIBOOT_FLAGS
    dd MULTIBOOT_CHECKSUM

section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

section .text
global _start
_start:
    ; Настройка стека
    mov esp, stack_top
    
    ; Очистка флагов
    cli
    
    ; Вызов ядра (БЕЗ подчеркивания для Linux)
    extern kernel_main
    call kernel_main
    
    ; Остановка
    cli
.hang:
    hlt
    jmp .hang
