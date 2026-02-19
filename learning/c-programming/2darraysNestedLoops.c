#include <stdio.h>
#include <stdlib.h>



int main(){

    // 2d array and multi arrays
    int nums[3][2] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };

    // nums[0][0] = 7 (would replace 1 with 7)

    printf("%d\n", nums[1][1]);

    // declare 2 variables
    int i,j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 2; j++) {
            printf("%d,", nums[i][j]);
        
        }
        printf("\n");
    }

    return 0;
}