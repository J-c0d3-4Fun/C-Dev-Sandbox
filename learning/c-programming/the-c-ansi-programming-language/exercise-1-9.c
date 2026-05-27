// Write a program to copy its input to its output,
// replacing each string of one or more blanks by a single blank.


#include <stdio.h>

int main() {

    int c,b;

    c = b = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            putchar(c);
            if (b == 0) {
                putchar(c);
                b = 1;
            
            }else {
                putchar(c);
                b = 0;
            }
            
        }

         
    }


}