// Write a program to print a histogram of the frequencies of different characters in its input

#include <stdio.h>

int main(){
    int c, i,j,state;
    // out of a word 0 inside a word 1
    c = i = j = state = 0;
    // to keep count of characters
    // represents 128 ascii charcters -> real characters
    int coccurence[128];
    

    for (i = 0; i < 128; ++i)
        coccurence[i] = 0;

    while ((c = getchar()) != EOF) {
        // think of the c as the key
        // array[key]++ so if c = '97' it equals 'a' in ascii
          ++coccurence[c];

    }
    for (i = 0; i < 128; ++i) {
        printf("index %d:", i );
        for (j = 0; j < coccurence[i]; ++j)
            printf("*");
        printf("\n");
    }
    
        
  
}