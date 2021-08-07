/** Interrupt ReQuest */
#include "interrupts.h"


void *irq_handlers[IRQ_SIZE] = {
    0, 0, 0, 0,  0, 0, 0, 0,
    0, 0, 0, 0,  0, 0, 0, 0
};


void irq_install_handler(int port, void (*handler)(registers_t *regs))
{
    irq_handlers[port] = handler;
}

void irq_remove_handler(int port)
{
    irq_handlers[port] = 0;
}

void irq_handler(registers_t *regs)
{
    void (*handler)(registers_t *regs);

    handler = irq_handlers[regs->int_no - 32];
    if (handler) {
        handler(regs);
    }

    if (regs->int_no >= 40) {
        outportb(0xA0, 0x20);
    }

    outportb(0x20, 0x20);
}


void irq_reset(void)
{
    // ICW1 - begin initialization
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    // ICW2 - remap offset address of IDT
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    // ICW3 - setup cascading
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    // ICW4 - environment info
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    // mask interrupts
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

void irq_init(void)
{
    irq_reset();

    idt_set_gate(32,  (unsigned)irq0, 0x08, 0x8e);
    idt_set_gate(33,  (unsigned)irq1, 0x08, 0x8e);
    idt_set_gate(34,  (unsigned)irq2, 0x08, 0x8e);
    idt_set_gate(35,  (unsigned)irq3, 0x08, 0x8e);
    idt_set_gate(36,  (unsigned)irq4, 0x08, 0x8e);
    idt_set_gate(37,  (unsigned)irq5, 0x08, 0x8e);
    idt_set_gate(38,  (unsigned)irq6, 0x08, 0x8e);
    idt_set_gate(39,  (unsigned)irq7, 0x08, 0x8e);

    idt_set_gate(40,  (unsigned)irq8, 0x08, 0x8e);
    idt_set_gate(41,  (unsigned)irq9, 0x08, 0x8e);
    idt_set_gate(42, (unsigned)irq10, 0x08, 0x8e);
    idt_set_gate(43, (unsigned)irq11, 0x08, 0x8e);
    idt_set_gate(44, (unsigned)irq12, 0x08, 0x8e);
    idt_set_gate(45, (unsigned)irq13, 0x08, 0x8e);
    idt_set_gate(46, (unsigned)irq14, 0x08, 0x8e);
    idt_set_gate(47, (unsigned)irq15, 0x08, 0x8e);
}
