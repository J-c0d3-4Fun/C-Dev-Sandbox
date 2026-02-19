#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("%f", 8.9);

    printf("%f", 5.0 + 5.5);
    printf("%f", 5.0 * 5.5);
    printf("%f", 5.0 / 5.5);
    printf("%f", 5.0 - 5.5);


    // int + decimal = decimal (floating point number)
    printf("%f", 5 + 4.5);

    // int / int will always return an integer
    printf("%d", 5 / 4);
    printf("%f", 5 / 4.0);


    // FUNCTIONS

    // power, 1position ^ 2position , in the example  4^3 
    printf("%f", pow(4, 3));

    // square root gives you the square root of a number
    printf("%f", sqrt(4));

    // ceiling gives you the next highest number, think of it is rounding up
    printf("%f", ceil(36.65));

    // floor rounds it down
    printf("%f", floor(45.23));

    return 0;
}