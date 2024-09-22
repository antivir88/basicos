/** Global Descriptor Table */
#include "interrupts.h"


struct GDT_entry GDT[GDT_SIZE]; // глобальные дескрипторы
struct GDT_ptr gdt_ptr;


void gdt_set_gate(uint32 num, uint32 base, uint32 limit, uint8 access, uint8 gran)
{
    // Setup the descriptor base address
    GDT[num].base_low = (base & 0xFFFF);
    GDT[num].base_middle = (base >> 16) & 0xFF;
    GDT[num].base_high = (base >> 24) & 0xFF;

    // Setup the descriptor limits
    GDT[num].limit_low = (limit & 0xFFFF);
    GDT[num].granularity = ((limit >> 16) & 0x0F);

    // Finally, set up the granularity and access flags
    GDT[num].granularity |= (gran & 0xF0);
    GDT[num].access = access;
}

void gdt_init(void)
{
    gdt_ptr.limit = (sizeof(struct GDT_entry) * GDT_SIZE) - 1;
    gdt_ptr.base = (uint32)&GDT;

    gdt_set_gate(0, 0, 0, 0, 0);                // Нулевой сегмент
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Сегмент кода
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Сегмент данных
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // Сегмент кода уровня пользовательских процессов
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // Сегмент данных уровня пользовательских процессов

    load_gdt();


    // Initialize TSS
    //tss_init(5, 0x10, 0);

    //load_tss();
}
