// Write a program that prints its input one word per line



#include <stdio.h>


int main() {

    int c, state;

    
    

    //  start outside the first character
    state = 0;
    c  = 0;
    while ((c = getchar()) != EOF ) {

        if (c == ' ' || c == '\n' || c == '\t') {
                if (state) {
                    putchar('\n');
                    state = 0;
                } 
            
        }else {
                putchar(c);
                state = 1;
            }


    }
}

