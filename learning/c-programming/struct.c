
# include <string.h>
#include <stdio.h>
#include <stdlib.h>

//  structs hold data/fields

struct Student{
    // define different attributes of a Student
    char name[50];
    char major[50];
    int age;
    double gpa;
};

int main(){


    // create an instance of the Student struct
    // created a container called student1 that can hold a name, major, age and gpa
    struct Student student1;
    // this student1 container's age is 22
    student1.age = 22;
    student1.gpa = 3.2;
    // use the string copy function to give a value to the array
    strcpy(student1.name, "Jim");
    strcpy(student1.major, "Business");

    struct Student student2;
    // this student1 container's age is 22
    student2.age = 45;
    student2.gpa = 4.1;
    strcpy(student2.name, "Pam");
    strcpy(student2.major, "Nursing");


    printf("%f\n", student1.gpa);
    printf("%s\n", student1.name);

    printf("%f\n", student2.gpa);
    printf("%s\n", student2.name);

    return 0;
}