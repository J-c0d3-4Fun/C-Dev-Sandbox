#include <stdio.h>
#include <stdlib.h>


int main(){
    // memory address = the place where c stores values
    int age = 30;
    double gpa = 3.4;
    char grade = 'A';


    // print physical memory address
    // %p = pointer
    printf("age: %p\n gpa: %p\n grade: %p", &age, &gpa, &grade);

    // output
    // age: 0x16bd9acfc
    // gpa: 0x16bd9acf0
    // grade: 0x16bd9acef%       
}