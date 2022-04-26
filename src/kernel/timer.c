// #include "framebuffer.h"
#include "interrupts.h"


int timer_ticks = 0;


void timer_handler(registers_t *regs)
{
    timer_ticks++;

    if (timer_ticks % 18 == 0) {
        // framebuffer_putString("One Second");
    }
}

void timer_wait(int ticks)
{
    int eticks;

    eticks = timer_ticks + ticks;

    while(timer_ticks < eticks);
}

void timer_init(void)
{
    irq_install_handler(0, timer_handler);
}
