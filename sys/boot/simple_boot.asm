[BITS 16]
[ORG 0x7C00]

start:
    ; Очистить экран
    mov ax, 0x0003
    int 0x10
    
    ; Установить цвет фона 
    mov ah, 0x06
    mov al, 0x00
    mov bh, 0x17    ; Белый текст 
    mov cx, 0x0000
    mov dx, 0x184F
    int 0x10
    
    ; Заголовок ОС
    mov dh, 3
    mov dl, 30
    call set_cursor
    mov si, os_title
    call print_string_color
    
    ; Версия
    mov dh, 5
    mov dl, 28
    call set_cursor
    mov si, version
    call print_string_color
    
    ; Автор
    mov dh, 6
    mov dl, 27
    call set_cursor
    mov si, author
    call print_string_color
    
    ; Описание
    mov dh, 9
    mov dl, 20
    call set_cursor
    mov si, desc1
    call print_string_color
    
    mov dh, 10
    mov dl, 22
    call set_cursor
    mov si, desc2
    call print_string_color
    
    ; Статус загрузки
    mov dh, 13
    mov dl, 25
    call set_cursor
    mov si, loading
    call print_string_color
    
    ; Системная информация
    mov dh, 16
    mov dl, 15
    call set_cursor
    mov si, sys_info1
    call print_string_color
    
    mov dh, 17
    mov dl, 15
    call set_cursor
    mov si, sys_info2
    call print_string_color
    
    mov dh, 18
    mov dl, 15
    call set_cursor
    mov si, sys_info3
    call print_string_color
    
    mov dh, 21
    mov dl, 20
    call set_cursor
    mov si, instruction
    call print_string_color
    
    ; Бесконечный 
    jmp $

set_cursor:
    mov ah, 0x02
    mov bh, 0x00
    int 0x10
    ret

print_string_color:
    mov ah, 0x0E
    mov bh, 0x00
    mov bl, 0x0F    ; я/б
.repeat:
    lodsb
    cmp al, 0
    je .done
    int 0x10
    jmp .repeat
.done:
    ret

; Текстовые данные
os_title    db 'ATHENA OS', 0
version     db 'Version 1.0.0', 0
author      db 'Created by Morcc', 0

desc1       db 'Simple Operating System', 0
desc2       db 'Assembly & C++ Edition', 0

loading     db 'System Ready!', 0

sys_info1   db 'Architecture: x86 (32-bit)', 0
sys_info2   db 'Memory: Basic VGA Text Mode', 0
sys_info3   db 'Status: Operational', 0

instruction db 'Welcome to Athena OS!', 0

; Заполнить до 510 байт ТАК КАК БОЛЬШЕ НЕЗЯ(
times 510-($-$$) db 0
; Сигнатура загрузочного сектора
dw 0xAA55
