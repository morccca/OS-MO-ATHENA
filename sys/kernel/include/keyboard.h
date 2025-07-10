#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "ports.h" 

class Keyboard 
{
public:
   
    static char getchar();

    static void wait_for_enter();

    static char scancode_to_ascii(uint8_t scancode);
};

#endif