#include <stdio.h>
#include <stdlib.h>

int main()
{
    // a function that can print text
    printf("Hello World");

    printf("Hello \n World");

    printf("Hello \"World");

    // format specifier , tells the printf function that we want to print data that's not just text
    // % <-- helps specify

    // %d allows us to include integers 
    printf("%d", 500);

    printf("My favorite number is %d", 500);

    // %s allows us to include text

    printf("My favorite %s is %d", "number", 500);

    // %f prints out a decimal number
    printf("My favorite %s is %f", "number", 5.0);

    // printing a integer using the variable name and %d integer specifier
    int favNum = 90;
    printf("My favorite %s is %d", "number", favNum);

    // %c allows you to print out a character
    char myChar = 'j';
     printf("My favorite character is %c", myChar);

    return 0;
}