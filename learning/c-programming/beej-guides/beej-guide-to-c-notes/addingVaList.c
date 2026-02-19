
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int add(int count, ...){
    int total = 0;
    va_list va;
    
    va_start(va, count);

    for (int i = 0; i < count; i++){
        int n = va_arg(va, int);

        total += n;

    }

    va_end(va);

    return total;
}

int main(void){

    printf("%d\n", add(4, 3, 6, 8, 9,10));
    printf("%d\n", add(4, 25, 9,12));
}