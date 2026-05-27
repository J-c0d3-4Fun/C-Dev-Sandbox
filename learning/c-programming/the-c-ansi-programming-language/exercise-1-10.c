// Write a program to copy its input to its output, 
// replacing each tab by \t, each backspace by \b, and each backslash by \\
// Thus makes tabs and backspaces visible in an unambiguous way


#include <stdio.h>

int main() {

    int c;

    c = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t' ||c == '\b' || c == '\\') {
            if ( c == '\t') {
                putchar('\\');
                putchar('t');
            }else if (c == '\b') {
                putchar('\\');
                putchar('b');
            }else if (c == '\\') {
                putchar('\\');
                putchar('\\');
            } 

        }else {
                putchar(c);
            }
    }
}