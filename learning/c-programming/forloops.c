#include <stdio.h>
#include <stdlib.h>


int main(){

    int luckNumbers[] = {4, 8, 15, 16, 23, 42}
;
    // for loop allows us to take this code and condense it
    // int i = 1;
    // while ( i <= 5) {
    //     printf("%d\n", i);
    //     i++;
    // }

    int i;
    for (i = 0; i < 6; i++) {
        printf("%d\n", luckNumbers[i]);
    }

    return 0;
}