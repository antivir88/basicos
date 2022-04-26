#include "stdio.h"
#include "stdarg.h"
#include "stdint.h"
#include "string.h"

#include "framebuffer.h"

// out_char
// out_string






const char digits[] = "0123456789ABCDEF";
char num_buffer[65];

char* int_to_str(size_t value, unsigned char base)
{
    size_t i = sizeof(num_buffer) - 1;
    num_buffer[i--] = '\0';

    do {
        num_buffer[i--] = digits[value % base];
        value = value / base;
    } while (value);

    return &num_buffer[i + 1];
}

/*
Наш printf понимает следующие форматы:
%s - Вывод строки.
%c - Вывод символа с указанным кодом
%b - Вывод числа в двоичном представлении
%o - Вывод числа в восьмеричном представлении
%d - Вывод числа в десятичном представлении
%x - Вывод числа в шестнадцатеричном представлении
%% - Вывод символа процента 
 */
void printf(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            size_t arg = va_arg(args, size_t);

            switch (*fmt) {
                case '%':
                    framebuffer_putChar('%');
                    break;
                case 'c':
                    framebuffer_putChar(arg);
                    break;
                case 's':
                    framebuffer_putString((char*)arg);
                    break;
                case 'b':
                    framebuffer_putString(int_to_str(arg, 2));
                    break;
                case 'o':
                    framebuffer_putString(int_to_str(arg, 8));
                    break;
                case 'd':
                    framebuffer_putString(int_to_str(arg, 10));
                    break;
                case 'x':
                    framebuffer_putString(int_to_str(arg, 16));
                    break;
            }
        } else {
            framebuffer_putChar(*fmt);
        }

        fmt++;
    }
    va_end(args);
}
