#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


void *memoryCopy(void *source, void *destination, int *byteCount){

    // conversions from void to char type
    char *s = source, *d = destination;

    // dereference and copy
    // here we decrement byteCount until it becomes 0 which is equal to false
    // byteCount is decremented after the expression is evaluated (Post decrement)
    while (byteCount--) {
        // assign and copy the byte, after the assignment is made increment to the next memory address
        *d++ = *s++;
    }
    return destination;
}

int main(void){

    return 0;
}