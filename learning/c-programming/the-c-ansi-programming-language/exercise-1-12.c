// Write a program that prints its input one word per line


#include <stdio.h>



int main(){
    int c, state;
    //  0 = outside , inside = 1
    c = state = 0;

    while ((c = getchar()) != EOF ) {
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state == 1) {
                putchar('\n');
                state = 0;
            }    
            
        } else {
            putchar(c);
            state = 1;
        }
           
           
            }
        

}