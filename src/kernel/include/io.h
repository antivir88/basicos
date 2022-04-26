#ifndef IO_H
#define IO_H

#include "stdint.h"

void outportb(uint16 port, uint8 value);
void outportw(uint16 port, uint16 value);
void outportl(uint16 port, uint32 value);
uint8  inportb(uint16 port);
uint16 inportw(uint16 port);
uint32 inportl(uint16 port);

#endif
