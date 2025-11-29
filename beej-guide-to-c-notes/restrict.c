#include <stdio.h>
#include <stdlib.h>


void swap(int *restrict a, int *restrict b){

    int t;

    t = *a;
    *a = *b;
    *b = t;
}


int main(void){

    int x = 10, y =20;

    // OK because a and b point to different things
    swap(&x, &y);

    //  Undefined behavior because a and b point to the same thing 
    swap(&x, &x);



    return 0;
}
