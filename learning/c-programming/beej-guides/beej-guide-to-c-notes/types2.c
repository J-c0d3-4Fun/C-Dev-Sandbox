#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

// this just has information is what I think is important/dont already know about programming 

// NEW HEADER ADDITION ALERT!
// <limits.h>
// defines macros that hold minimum and maximum integer values
// NOTE IMPORTANT!: never hardcode or assume these values
// <float.h>
// some macros: float, double, long double (in order of precision with float being the least precise)




// ASCII
/*
first 128 characters, the character constant will be 
converted to a char whose value is the same as the ASCII value of the character
One of the most popular character sets today is Unicode99 (which is a superset of ASCII), 
so for your basic 0-9, A-Z, a-z and punctuation, you’ll almost certainly get the ASCII values out of them.
*/

// char type
//  is actually an integer
//  can be signed and unsigned <- like int

// new types
/*
short int
long long int



*/


int main (void) {

    long long int p;
    long long x;
    short y;
    short int o;

    char a = 10;
    char b = 'C';

    printf("the result: %d", a  + b);
   
//  case doesnt matter for hex digits
   int g = 0x1A2B; // Hexadecimal 

   int n = 012; // Octal number, "12"
   
   
    return 0;

}