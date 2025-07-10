#include "ports.h"

// Чтение байта из порта
uint8_t Ports::inb(uint16_t port) 
{
    uint8_t result;
    asm volatile("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Запись байта в порт
void Ports::outb(uint16_t port, uint8_t val) 
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}