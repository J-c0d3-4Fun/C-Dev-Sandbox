#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void *myMemcopy(void *dest, const void *src, size_t n){

    const unsigned char *s = src;
    unsigned char *d = dest;

    while(n-- > 0) // For the given number of bytes
    *d++ = *s++;    // Copy source byte to dest byte

return dest;
}
