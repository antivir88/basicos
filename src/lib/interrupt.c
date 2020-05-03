#include "stdlib.h"
#include "interrupt.h"


typedef struct {
    uint16 address_0_15;
    uint16 selector;
    uint8 reserved;
    uint8 type;
    uint16 address_16_31;
} __attribute__((packed)) IntDesc;

typedef struct {
    uint16 limit;
    void *base;
} __attribute__((packed)) IDTR;

IntDesc *idt = (void*)0xFFFFC000;


void timer_int_handler();


void init_interrupts() {
    *((size_t*)0xFFFFEFF0) = 0x8000 | 3;

    memset(idt, 0, 256 * sizeof(IntDesc));

    IDTR idtr = {256 * sizeof(IntDesc), idt};

    asm volatile("lidt (,%0,)"::"a"(&idtr));

    irq_base = 0x20;
    irq_count = 16;

    outb(0x20, 0x11);
    outb(0x21, irq_base);
    outb(0x21, 4);
    outb(0x21, 1);
    outb(0xA0, 0x11);
    outb(0xA1, irq_base + 8);
    outb(0xA1, 2);
    outb(0xA1, 1);
    
    set_int_handler(irq_base, timer_int_handler, 0x8E);
    asm volatile("sti");
}


void set_int_handler(uint8 index, void *handler, uint8 type)
{
	asm volatile("pushf \n cli");

	idt[index].selector = 8;
	idt[index].address_0_15 = (size_t)handler & 0xFFFF;
	idt[index].address_16_31 = (size_t)handler >> 16;
	idt[index].type = type;
	idt[index].reserved = 0;

	asm volatile("popf"); 
}

IRQ_HANDLER(timer_int_handler) {
    (*((char*)(0xB8000 + 79 * 2)))++;
}
