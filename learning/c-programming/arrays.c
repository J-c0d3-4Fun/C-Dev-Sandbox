#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int luckyNumbers[] = {4, 8, 15, 16, 23, 42};

    // create an array without declaring values
    // you must tell c how many elements the array can hold
    int luckyNumbers2[20];
    luckyNumbers2[0] = 70;

    

    // assign a different value to a specific position in the index
    luckyNumbers[1] = 200;

    // index goes inside the square brackets []
    printf("%d\n", luckyNumbers[1]);
    printf("%d", luckyNumbers2[0]);
    return 0;
}