#include "stdlib.h"

int strlen(char *src)
{
    int i = 0;

    while (*src++) {
        i++;
    }

    return i;
}
