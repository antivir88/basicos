#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "framebuffer.h"
#include "stdint.h"


#define IRQ_SIZE 16
#define GDT_SIZE 5
#define IDT_SIZE 256

#define KEYBOARD_BUF_SIZE 64


//--------------------TSS
typedef struct tss_entry {
    uint32 prev_tss;
    uint32 esp0;
    uint32 ss0;
    uint32 esp1;
    uint32 ss1;
    uint32 esp2;
    uint32 ss2;
    uint32 cr3;
    uint32 eip;
    uint32 eflags;
    uint32 eax;
    uint32 ecx;
    uint32 edx;
    uint32 ebx;
    uint32 esp;
    uint32 ebp;
    uint32 esi;
    uint32 edi;
    uint32 es;
    uint32 cs;
    uint32 ss;
    uint32 ds;
    uint32 fs;
    uint32 gs;
    uint32 ldt;
    uint16 trap;
    uint16 iomap_base;
} __attribute__((packed)) tss_entry_t;
//--------------------TSS

//--------------------GDT
struct GDT_entry {
    uint16 limit_low;  // Младшие 16 бит смещения
    uint16 base_low;   // Младшие 16 бит базы
    uint8  base_middle; // Следующие восемь бит базы
    uint8  access;      // Флаг определяет уровень доступа
    uint8  granularity;
    uint8  base_high;   // старшие 8 бит базы
} __attribute__((packed));

struct GDT_ptr {
    uint16 limit; // старшие 16 бит смещения селектора
    uint32 base;  // адрес первой структуры GDT_entry
} __attribute__((packed));
//--------------------GDT


//--------------------IDT
struct IDT_entry {
    uint16 offset_lowerbits;      // младшие 16 бит смещения
    uint16 selector;              // Селектор сегмента кода из GDT или LDT
    uint8 zero;                           // не используется, всегда ноль
    uint8 type_attr;                      // тип и аттрибуты
    uint16 offset_higherbits; // старшие 16 бит смещения
} __attribute__((packed));

struct IDT_ptr {
    uint16 limit; // старшие 16 бит смещения селектора
    uint32 base; // адрес первой структуры IDT_entry
} __attribute__((packed));
//--------------------IDT


typedef struct registers {
    uint32 ds, gs, fs, es; // Селектор сегмента данных
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 int_no, err_code;
    uint32 eip, cs, eflags, useresp, ss;
} registers_t;

typedef struct {
    uint8 buffer[KEYBOARD_BUF_SIZE];
    uint8 *head;
    uint8 *tail;
} keyboard_buffer_t;

// keybuffer
void keyboard_buffer_init(void);
void keyboard_buffer_scan(uint8 scancode);
void keyboard_buffer_enqueue(uint8 ascii);
uint8 keyboard_buffer_dequeue(void);


// install
void interrupts_init(void);

void gdt_init(void);
void idt_init(void);
void irq_init(void);
void isr_init(void);
void tss_init(uint32 idx, uint32 kss, uint32 kesp);

void keyboard_init(void);
void timer_init(void);

void interrupts_run(void);


// handlers installers
void irq_install_handler(int port, void (*handler)(registers_t *regs));
void irq_remove_handler(int port);


// gates
void idt_set_gate(uint8 num, uint64 base, uint16 sel, uint8 flags);
void gdt_set_gate(uint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran);
void tss_set_stack(uint32 kss, uint32 kesp);


// hardcode
void   *memset(void *dest, int val, int len);
uint16 *memsetw(uint16 *dest, uint16 val, size_t count);
void   *memcpy(void *dest, const void *src, size_t count);
size_t strlen(const char *str);

void outportb(uint16 port, uint8 value);
uint8 inportb(uint16 port);


// exception and IRQ handler
void isr_handler(registers_t *regs);
void irq_handler(registers_t *regs);


// from ASM

extern void load_gdt(void);
extern void load_idt(void);
extern void load_tss(void);

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

extern void  irq0(void);
extern void  irq1(void);
extern void  irq2(void);
extern void  irq3(void);
extern void  irq4(void);
extern void  irq5(void);
extern void  irq6(void);
extern void  irq7(void);
extern void  irq8(void);
extern void  irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);


#endif
