// Write a program to print a histogram of length of words in its input. 
// It is easy to draw the histogram with the bars horizontal
// a vertical orientation is mor challenging





#include <stdio.h>


int main(){



    int c, i,j, state;
    int woccurence[20];
    int wlength = 0;

    for (i = 0; i < 20; ++i) {
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
    if (state == 1)
        ++woccurence[wlength];
    printf("Histogram ");
        for (i = 0; i < 20; ++i) {
        printf("%d ",i);
        for (j = 0;j < woccurence[i]; ++j) {
            printf("*");
        }
        printf("\n");
        
    }
}