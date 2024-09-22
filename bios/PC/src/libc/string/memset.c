#include "string.h"

void memset(uint8 *dest, uint8 val, uint32 len)
{
    /*uint8 *temp = (uint8 *)dest;

    for ( ; len != 0; len--) {
        *temp++ = val;
    }*/
	asm volatile("movl %0, %%eax \n movl %1, %%edi \n movl %2, %%ecx \n rep stosl"
		::"a"((uint32)val | ((uint32)val << 8) | ((uint32)val << 16) | ((uint32)val << 24)),"b"(dest),"c"(len >> 2));
	asm volatile("movb %b0, %%al \n movl %1, %%ecx \n rep stosb"::"a"(val),"b"(len & 3));
}
