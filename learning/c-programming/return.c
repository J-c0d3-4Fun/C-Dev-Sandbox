#include <stdio.h>
#include <stdlib.h>

// return values must be above the function calling it
double cube(double numb){
    double result = numb * numb * numb;
    // break out the function ad return it <- auto exits the function so code wont print if its after this line
    return result;
}

int main(){

    printf("Answer: %f", cube(3.0));


    return 0;
}