#include "interrupts.h"
#include "shell.h"

#include "stdio.h"


//
typedef struct {
	uint64 base;
	uint64 size;
} BootModuleInfo;


// kernel
int kmain(uint8 boot_disk_id, void *memory_map, BootModuleInfo *boot_module_list) {

    interrupts_init(); // инит векторов

    framebuffer_init();

    timer_init(); // внедряем таймер
    keyboard_init(); // внедряем клаву

    interrupts_run(); // запускаемся

    // system info

    printf("Boot disk id is %d\n", boot_disk_id);
    printf("Memory map at 0x%x\n", memory_map);
    printf("Boot module list at 0x%x\n", boot_module_list);
    printf("String is %s, char is %c, number is %d, hex number is 0x%x", __DATE__, 'A', 1234, 0x1234);

    // system started

    shell(); // тут вопрос

    while(1) asm("hlt"); // петля

    return 0xdeadbaba; // код возврата требуемый
}
