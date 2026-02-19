
#include <stdio.h>
#include <stdlib.h>


int main()
{
    // declaring the variable without giving it a value
    int age;
    double gpa;
    char grade;
    // not giving the variable a value, need to tell c how big the variable can be. (how many characters this variable can store)
    char name[20];

    // prompt the user
    printf("Enter your age: ");
    // scanf allows users to input something into the program
    // pointer to the variable age
    scanf("%d", &age);
    printf("Your are %d years old", age);


    // prompt the user
    printf("Enter your gpa: ");

    // REMEMBER! looking for a double
    scanf("%lf", &gpa);
    printf("Your gpa is %f ", gpa);

    
    // prompt the user
    printf("Enter your grade: ");
    scanf("%c", &grade);
    printf("Your grade is %c", grade);

  
    // prompt the user
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Your name is %s", name);

    // fgets grabs a whole line of text, can only store inside a string of characters
    printf("Enter your name: ");
    fgets(name, 20, stdin);
    printf("Your name is %s", name);

    return 0;
}