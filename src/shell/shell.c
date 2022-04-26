#include "shell.h"
#include "framebuffer.h"
#include "interrupts.h"

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



#define C_ENDL '\0'

int strcmp(char *str1, char *str2) // str1=res , str2=F1
{
    int i = 0;
    int failed = 1;

    while(str1[i] != C_ENDL && str2[i] != C_ENDL) {
        if(str1[i] != str2[i]) {
            failed = 0;
            break;
        }

        i++;
    }

    if( (str1[i] == C_ENDL && str2[i] != C_ENDL) || (str1[i] != C_ENDL && str2[i] == C_ENDL) ) {
        failed = 0;
    }
  
    return failed;
}




uint8 getchar(void)
{
    uint8 ascii = 0;
    while (ascii == 0) {
        ascii = keyboard_buffer_dequeue();
    }
    return ascii;
}

char* getString(char* result)
{
    char buf;

    int a=0;
    while ((buf = getchar()) != '\n') {
        result[a] = buf;
        a++;
    }

    return result;
}

void shell(void)
{
    framebuffer_putString("");
    framebuffer_putString("                                   Basic OS                                        ");
    framebuffer_setTextColor(VGA_COLOR_BLACK, VGA_COLOR_GREEN);
    framebuffer_putString("2022 (c) Zcasper");
    framebuffer_setTextColor(VGA_COLOR_CYAN, VGA_COLOR_BLUE);
    framebuffer_putString("");
    framebuffer_putString("");
    framebuffer_putString("BIOS -> BasicOS");
    framebuffer_putString("");
    framebuffer_putString("");

    for (;;) {
        char str[127] = "";
        char* res = getString(str);

        if (strcmp(res, "F1") != 0) {
            framebuffer_putString("HELP not found!");
        } else if (strcmp(res, "F12")) {
            framebuffer_putString("Go sleep stupid user!");
        } else {
            framebuffer_putString(res);
        }
    }
}
