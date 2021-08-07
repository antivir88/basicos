#include "interrupts.h"
#include "shell.h"

//typedef struct {
//	uint64 base;
//	uint64 size;
//} BootModuleInfo;



uint8 getchar(void)
{
    uint8 ascii = 0;
    while (ascii == 0) {
        ascii = keyboard_buffer_dequeue();
    }
    return ascii;
}



//int kmain(uint8 boot_disk_id, void *memory_map, BootModuleInfo *boot_module_list) {
int kmain(void) {
    interrupts_init();

    framebuffer_init();
    timer_init();
    keyboard_init();

    interrupts_run(); // activate

    shell();

    while(1) asm("hlt");

    return 0xdeadbaba;
}
