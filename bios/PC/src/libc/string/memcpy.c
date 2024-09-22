#include "string.h"

void memcpy(void *dest, void *src, uint32 len)
{
    const uint8 *sp = (const uint8 *)src;
    uint8 *dp = (uint8 *)dest;

    for(; len != 0; len--) {
        *dp++ = *sp++;
    }
}
