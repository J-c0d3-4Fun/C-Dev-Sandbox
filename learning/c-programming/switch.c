#include <stdio.h>
#include <stdlib.h>



int main(){
    char grade = 'Z';

    switch (grade) {
        case 'A' :
        printf("You did great! ");
        break;
        case 'B' :
        printf("You did good! ");
        break;
        case 'C':
        printf("You did ok ");
        break;
        case 'D':
        printf("You did poorly ");
        break;
        case 'F':
        printf("You failed ");
        break;
        default:
        printf("You dont have a grade!");

    }


    return 0;
}