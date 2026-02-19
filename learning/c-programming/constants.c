#include <stdio.h>
#include <stdlib.h>

int main()
{
    // constants cannot be modified
    const int age = 40;
    printf("my age is %d", age);

    // age = 41; <-- causes compiler error
    // printf("my age is %d", age);

    return 0;
}