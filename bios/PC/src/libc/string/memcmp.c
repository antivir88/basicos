#include "string.h"

int memcmp(const char *s1, const char *s2, size_t n)
{
    if (!n) {
        return 0;
    }

    while (--n && (*(char*)s1 == *(char*)s2)) {
        s1 = (char*)s1 + 1;
        s2 = (char*)s2 + 1;
    }

    return (*((unsigned char*)s1) - *((unsigned char*)s2));
}
