#include "interrupts.h"


tss_entry_t kernel_tss;


void tss_init(uint32 idx, uint32 kss, uint32 kesp)
{
    uint32 base = (uint32)&kernel_tss;

    gdt_set_gate(idx, base, base + sizeof(tss_entry_t), 0xE9, 0);

    memset(&kernel_tss, 0, sizeof(tss_entry_t));

    kernel_tss.ss0 = kss;
    kernel_tss.esp0 = kesp;

    kernel_tss.cs = 0x0b;
    kernel_tss.ds = 0x13;
    kernel_tss.es = 0x13;
    kernel_tss.fs = 0x13;
    kernel_tss.gs = 0x13;
    kernel_tss.ss = 0x13;
}

void tss_set_stack(uint32 kss, uint32 kesp)
{
    kernel_tss.ss0 = kss;
    kernel_tss.esp0 = kesp;
}
