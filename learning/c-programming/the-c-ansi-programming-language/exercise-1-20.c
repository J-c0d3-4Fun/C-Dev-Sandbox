// Write a program detab that replaces tabs in the input 
// with the proper number of blanks to space to the next tab stop
// Assume a fixed set of tab stops, say every n columns
// Should n be variable or a symbolic paremeter?

#define TABSTOP 8

#include <stdio.h>

int my_getline( char line[], int maxlength);


int main() {
    int c;
    int column = 0;
    int next_stop, spaces = 0;

    while ((c = getchar()) != EOF) {

         if (c == '\n') {
            column = 0;
            putchar(c);
        } else if (next_stop > column) {
                next_stop = ((column / TABSTOP) + 1) * TABSTOP;
                spaces = next_stop - column;
                for (int i = 0; i < spaces; i++) {
                    putchar(' ');
                }
                column = next_stop;
            } else {
            ++column;
            putchar(c);
        }
    } 

    return 0;
}

