#include "interrupts.h"


void interrupts_init(void)
{
	gdt_init();
	idt_init();
	isr_init();
	irq_init();
}
void interrupts_run(void)
{
	asm volatile("sti");
}


// ------ hardcodes ----------

// временно тут жить
void *memset(void *dest, int val, int len)
{
    char *temp = (char *)dest;

    for (; len != 0; len--) {
        *temp++ = (char)val;
    }

    return dest;
}

uint16 *memsetw(uint16 *dest, uint16 val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;

    for( ; count != 0; count--) {
        *temp++ = val;
    }

    return dest;
}

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;

    for(; count != 0; count--) {
        *dp++ = *sp++;
    }

    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;

    for(retval = 0; *str != '\0'; str++) {
        retval++;
    }

    return retval;
}
