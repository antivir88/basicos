#include "stdlib.h"
#include "interrupt.h"
#include "tty.h"

typedef struct {
	uint64 base;
	uint64 size;
} BootModuleInfo;




void isr_handler() {
}
void irq_handler() {
}

/* 0 - Black
// 1 - Blue
// 2 - Green
// 3 - Cyan
// 4 - Red
// 5 - Magenta
// 6 - Brown
// 7 - Light Grey
// 8 - Dark Grey
// 9 - Light Blue
// 10/a - Light Green
// 11/b - Light Cyan
// 12/c - Light Red
// 13/d - Light Magenta
// 14/e - Light Brown
// 15/f – White */

int kmain(uint8 boot_disk_id, void *memory_map, BootModuleInfo *boot_module_list) {
    // это всё круто но, инициализуем АПИ, форкаемся и уходим в вечный цикл

    //write_text("Happy+birthday+!", 0x0F00);
    //write_text("Happy+birthday+", 0x0E00);
    //write_text("Happy+birthday", 0x0D00);
    //write_text("Happy+birthda", 0x0C00);
    //write_text("Happy+birthd", 0x0B00);
    //write_text("Happy+birth", 0x0A00);
    //write_text("Happy+birt", 0x0900);
    //write_text("Happy+bir", 0x0800);
    //write_text("Happy+bi", 0x0700);
    //write_text("Happy+b", 0x0600);
    //write_text("Happy+", 0x0500);
    //write_text("Happy", 0x0400);
    //write_text("Happ", 0x0300);
    //write_text("Hap", 0x0200);
    //write_text("Ha", 0x0100);
    //write_text("H", 0x0000);

    //write_text("Welcome to BasicOS (x86)", 0x0F00);


	//init_interrupts();
    init_tty();
    set_text_attr(0x1a);
    clear_screen();
    out_string("very nice!\n");
    out_string("very nice too!\n");

	printf("Welcome to MyOS!\n");
	printf("Boot disk id is %d\n", boot_disk_id);
	printf("Memory map at 0x%x\n", memory_map);
	printf("Boot module list at 0x%x\n", boot_module_list);
	printf("String is %s, char is %c, number is %d, hex number is 0x%x", __DATE__, 'A', 1234, 0x1234);

    return 0xdeadbaba;

    // init();
    // for (;;) pause();
}


void init(void) {
    //
}

