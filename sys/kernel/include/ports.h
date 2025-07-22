#ifndef PORTS_HPP
#define PORTS_HPP

#include "types.h"

class Ports 
{
public:
    static uint8_t inb(uint16_t port);

    static void outb(uint16_t port, uint8_t val);
};

#endif 