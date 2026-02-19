#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// convert a number to a string use sprintf() or snprintf()

// atoi() & strtol()
// convert string to number
// apart of the <stdlib.h>
// NOTE!: These have bad error-handling characteristics 
// (including undefined behavior if you pass in a bad sting)
// really atoi() is "ASCII-to-integer"
// strtol handles errors better and has more conversion types and more bases
// can convert decimals (base 10)
// can also convert binary numbers (base 2)

// char conversion
// prints the UTF-8 (& ASCII) code pint for the character

// Implicit conversion
// int +/-/*// double = int
// float +/-/*// int = float

// Casting 
// you can explicitly change the type of an expression by putting a new
// type in parentheses in front of it
// i.e.
// int x = 10;
// long int y = (long int)x + 12;
// NOTE: <ctype.h> has more conversion functions



int main(void){

    char s[10];
    float f = 3.14159;
    char *pi = "3.1459";

    // Convert "f" to string, storing in "s", writing at most 10 characters
    snprintf(s, 10, "%f", f);
    printf("String value: %s\n", s);

    float j = atof(pi);
    printf("%f\n", f);


    char *t = "1738"; // Yea baby - Fetty wap


    // Convert t,  a number in base 10 to an unsigned long int.
    // NULL means we dont care to lean about any error information.
    // its a pointer to a pointer to a char <- if we had a variable there
    // char *badchar, *i = "34x90";
    // unsigned long o = strtoul(i, &badchar, 10);
    // and printed it out i.e. printf("%c:" *badchar) it would print the illegal character
    // if nothing goes wrong it points to the NULL character
    unsigned long o = strtoul(t, NULL, 10);
    printf("%lu\n", o);



    char p = '8';
    int x = p; // UTF-8 code point = 56

    // can also use addition to convert, int y = p + 0;
    int y = p - 0;  // Value 8




    // Casting
    int h = 10;
    int *d = &h;
    // generates a warning
    printf("%p\n", d);
    // fix it with casting
    printf("%p\n", (void*)d);



    return 0;
}