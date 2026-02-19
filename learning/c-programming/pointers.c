#include <stdio.h>
#include <stdlib.h>


int main(){

    // pointer is a type of data we can work with in our programs
    // resides in the memory address of our computers
    // pointer is a type of data that is the memory address

    int age = 30;
    
    double gpa = 3.4;
    char grade = 'A';
    // pointer variable - to create a pointer variable you need a physical memory address
    // inside the pointer variable you will store the memory address of another variable 
    int * pAge = &age;
    double * pGpa = &gpa;
    char * pGrade = &grade;


    // & - gives you the physical address in memory
    // we're passing the memory address to the %p pointer
    printf("age's memory address: %p\n", &age);
    printf("gpa's memory address: %p\n", &gpa);

    return 0;
}