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

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};


// реальный режим необходим в основном для инициализации системы


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
