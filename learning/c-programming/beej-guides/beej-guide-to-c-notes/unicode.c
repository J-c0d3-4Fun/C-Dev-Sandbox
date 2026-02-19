#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

// Code Points
// mean a numeric a value representing a character 
// ex: the numeric value 66 represents "B"
// tells us effectively the serial number of a particular character

// Encoding
// tells us how we're going to represent that number in memory


// Unicode in C
// specify unicode characters
// \u (16-bit Unicode) & \U 
// ex: \u20AC (case for the hex doesn't matter)
// caveat: you can't use \u or \U to 
// encode any points below 0xA0

// Different Character Types


// Multibyte Characters
// string (array of char) =  multibyte 
// strings made up of multibyte characters
// 

// remember! that strlen() returns the number 
// of bytes in the string, not th number of characters


// Wide Characters
// if its not multibyte character then its a wide character
// wide character strings are arrays characters 
// can be represented by number types
// wchar_t <- example of a type

// Using Wide Characters and wchar_t
// the main wide character type = wchar_t
// to use wchar_t, include <wchar.h>
// you can declare a string or character of this type
// with the "L" prefix and can print them with %ls 
// print an individual character %lc


// Wide Character Functionality


// wint_t  
// hold single characters (whether being passed or return)




int main(void){


    char *s = "\u20AC1.23";
    printf("%s\n", s);

    char c[128] = "Hello, world!"; // Multibyte string

    wchar_t *t = L"Hello, world!";
    wchar_t j = L'B';

    printf(" %ls %lc\n", s, c);


}