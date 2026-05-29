// Write a program to print a histogram of length of words in its input. 
// It is easy to draw the histogram with the bars horizontal
// a vertical orientation is mor challenging





#include <stdio.h>


int main(){



    int c, i, state;
    int woccurence[10];
    int wlength = 0;

    for (i = 0; i < 10; ++i) {
        woccurence[i] = 0;
    }

    // outside = 0 inside word = 1
    c = i = state = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t' || c == '\b') {
            if (state == 1) {
                state = 0;
                ++woccurence[wlength];
                wlength = 0;
            }
        } else {
            ++wlength;
            state = 1;
            
        }   
        
    }
    printf("WordLength = ");
        for (i = 0; i < 10; ++i) {
        printf("%d", woccurence[i]);
    }
}