#include <stdio.h>
#include <stdlib.h>


int main(void){
    int base = 10;

    int *p = malloc(sizeof(int) * base);

    unsigned i;

    // Assign them valuse 0-45, multiply i * 5
    for (i = 0; i < base; i++) {
        p[i] = i * 5;
    }

    for (i = 0; i < base; i++) {
        printf("%d\n", p[i]);
    }
    // DON'T FORGET TO FREE THE SPACE!
    free(p);

    return 0;
}