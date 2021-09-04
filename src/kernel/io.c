#include "io.h"

void outportb(uint16 port, uint8 value)
{
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

void outportw(uint16 port, uint16 value)
{
    asm volatile("outw %w1, %w0" : : "dN" (port), "a" (value));
}

void outportl(uint16 port, uint32 value)
{
    asm volatile("outl %1, %w0" : : "dN" (port), "a" (value));
}


uint8 inportb(uint16 port)
{
    uint8 ret;

    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}

uint16 inportw(uint16 port)
{
    uint16 ret;

    asm volatile("inw %w1, %w0" : "=a" (ret) : "dN" (port));

    return ret;
}

uint32 inportl(uint16 port)
{
    uint32 ret;

    asm volatile("inl %w1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}
