#include "stdlib.h"

void outb(uint16 port, uint8 value)
{
    asm volatile("outb %b1, %w0" : : "dN" (port), "a" (value));
}

void outw(uint16 port, uint8 value)
{
    asm volatile("outw %w1, %w0" : : "dN" (port), "a" (value));
}

void outl(uint16 port, uint8 value)
{
    //asm volatile("outl %1, %w0" : : "dN" (port), "a" (value));
    //Ошибка: «%al» не допускается вместе с «outl»
}

uint8 inb(uint16 port)
{
    uint8 ret;

    asm volatile("inb %w1, %b0" : "=a" (ret) : "dN" (port));

    return ret;
}

uint16 inw(uint16 port)
{
    uint16 ret;

    asm volatile("inw %w1, %w0" : "=a" (ret) : "dN" (port));

    return ret;
}

uint32 inl(uint16 port)
{
    uint32 ret;

    asm volatile("inl %w1, %0" : "=a" (ret) : "dN" (port));

    return ret;
}


void memcpy(void *dest, void *src, uint32 len)
{
    const uint8 *sp = (const uint8 *)src;
    uint8 *dp = (uint8 *)dest;

    for(; len != 0; len--) {
        *dp++ = *sp++;
    }
}

void memset(uint8 *dest, uint8 val, uint32 len)
{
    /*uint8 *temp = (uint8 *)dest;

    for ( ; len != 0; len--) {
        *temp++ = val;
    }*/
	asm("movl %0, %%eax \n movl %1, %%edi \n movl %2, %%ecx \n rep stosl"
		::"a"((uint32)val | ((uint32)val << 8) | ((uint32)val << 16) | ((uint32)val << 24)),"b"(dest),"c"(len >> 2));
	asm("movb %b0, %%al \n movl %1, %%ecx \n rep stosb"::"a"(val),"b"(len & 3));
}

void memset_word(void *mem, uint16 value, size_t count)
{
    asm("movl %0, %%eax \n movl %1, %%edi \n movl %2, %%ecx \n rep stosl"
        ::"a"((uint32)value | ((uint32)value << 16)),"b"(mem),"c"(count >> 1));
}

int strcmp(char *str1, char *str2)
{
    int i = 0;
    int failed = 0;

    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) {
            failed = 1;
            break;
        }

        i++;
    }

    if( (str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0') ) {
        failed = 1;
    }
  
    return failed;
}


void strcpy(char *dest, const char *src)
{
    do {
        *dest++ = *src++;
    } while (*src != 0);
}

char* strcat(char *dest, const char *src)
{
    while (*dest != 0) {
        *dest = *dest++;
    }

    do {
        *dest++ = *src++;
    } while (*src != 0);

    return dest;
}

int strlen(char *src)
{
    int i = 0;

    while (*src++) {
        i++;
    }

    return i;
}
