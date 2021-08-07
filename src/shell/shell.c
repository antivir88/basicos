#include "shell.h"
#include "framebuffer.h"


void shell(void)
{
    framebuffer_putString("");
    framebuffer_putString("                                   Basic OS                                        ");
    framebuffer_putString("2021 (c) Zcasper");
    framebuffer_putString("");
    framebuffer_putString("");

    for (;;) {
        framebuffer_putChar(getchar());
    }
}
