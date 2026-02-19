#include <stdio.h>
#include <stdlib.h>


int main(){
    
    int age = 30;
    int *pAge = &age;

    // this pointer variable is storing the address of an integer
    // grab the actual value stored at the physical address
    printf("%d\n", *pAge);
    printf("%d\n", *&age);
    printf("%p", &*&age);


    return 0;
}