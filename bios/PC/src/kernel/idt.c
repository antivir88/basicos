/** Interrupt Descriptor Table */
#include "interrupts.h"



struct IDT_entry IDT[IDT_SIZE]; // вектора прерываний
struct IDT_ptr idt_ptr;



void idt_set_gate(uint8 num, uint64 base, uint16 sel, uint8 flags)
{
    IDT[num].offset_lowerbits = base & 0xffff;
    IDT[num].offset_higherbits = (base >> 16) & 0xffff;
    IDT[num].selector = sel;
    IDT[num].zero = 0;
    IDT[num].type_attr = flags /* | 0x60 */; // enable for user-mode
}

void idt_init(void)
{
    idt_ptr.limit = (sizeof(struct IDT_entry) * IDT_SIZE) - 1;
    idt_ptr.base = (uint32)&IDT;

    memset(&IDT, 0, sizeof(struct IDT_entry) * IDT_SIZE);

    load_idt();
}
