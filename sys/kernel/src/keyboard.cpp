#include "keyboard.h"

static constexpr char KEYMAP[] = 
{
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 
    '-', '=', '\b', '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
    'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd', 'f', 'g', 'h', 
    'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};


char Keyboard::getchar() 
{
    // флаг 
    while (!(Ports::inb(0x64) & 0x01)) 
    {
        asm volatile("pause");
    }

    return Ports::inb(0x60);  
}

void Keyboard::wait_for_enter() 
{
    char key;
    do 
    {
        key = getchar();
        
        if (key & 0x80) continue;

    } 
    while (key != 0x1C);  
}

char Keyboard::scancode_to_ascii(uint8_t scancode) 
{

    if ((scancode & 0x80) || scancode >= sizeof(KEYMAP)) 
    {
        return 0;
    }
    
    return KEYMAP[scancode];
}