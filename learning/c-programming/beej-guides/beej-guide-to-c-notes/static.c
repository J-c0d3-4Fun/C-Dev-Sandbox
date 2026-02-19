#include <stdio.h>
#include <stdlib.h>

void counter(void){

    static int count = 1;
    printf("This has been called %d time(s)\n", count);

    count++;
}

int main(){

    // program starts a t 1 and then increments after each call
    // the value persist between calls
    counter();
    counter();
    counter();
    counter();
    counter();
    counter();

    return 0;
}