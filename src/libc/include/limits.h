#ifndef LIMITS_H
#define LIMITS_H

/**
 * Содержит заранее заданные константы, определяющие специфику реализации
 * свойств целых типов, как, например, область допустимых значений (_MIN, _MAX). 
 */

// DEFINITIONS

// Число бит в байте
#define CHAR_BIT   8
// Минимальное значение для знакового char
#define SCHAR_MIN  -128
// Максимальное значение для знакового char
#define SCHAR_MAX  127
// Максимальное значение для беззнакового char
#define UCHAR_MAX  255
// Минимальное значение для char
#define CHAR_MIN   -128
// Максимальное значение для char
#define CHAR_MAX   127
// Максимальная многобайтовая длина символа по всем локалям
#define MB_LEN_MAX 4
// Минимальное значение для short int
#define SHRT_MIN   -32768
// Максимальное значение для short int
#define SHRT_MAX   32767
// Максимальное значение для беззнакового short int
#define USHRT_MAX  65535
// Минимальное значение для int
#define INT_MIN    −2147483648
// Максимальное значение для int
#define INT_MAX    2147483647
// Максимальное значение для беззнакового int
#define UINT_MAX   4294967295
// Минимальное значение для long int
#define LONG_MIN   −9223372036854775808
// Максимальное значение для long int
#define LONG_MAX   9223372036854775807
// Максимальное значение для беззнакового long int
#define ULONG_MAX  18446744073709551615
// Минимальное значение для long long int
#define LLONG_MIN  −9223372036854775808
// Максимальное значение для long long int
#define LLONG_MAX  9223372036854775807
// Максимальное значение для беззнакового long long int
#define ULLONG_MAX 18446744073709551615


// METHODS


#endif
