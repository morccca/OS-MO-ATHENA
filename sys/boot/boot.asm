; не рабочая тема уже
bits 32

section .text
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00) 

global start
extern OSmain

start:
    cli
    mov esp, stack_space
    call OSmain
    hlt 

section .bss
    resb 8192
stack_space:
