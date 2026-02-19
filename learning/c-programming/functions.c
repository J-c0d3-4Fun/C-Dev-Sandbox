#include <stdio.h>
#include <stdlib.h>

// must declare before using function 
// void sayHi();

// must prototype first = specify parameter
// void sayHi(char name[]) <- must specify the parameter

// this is because we are declaring the function after the main method

void sayHi(char name[], int age);

int main()
{
    printf("Top\n");
    sayHi("Mike", 40);
    sayHi("Tom", 35);
    sayHi("Oscar", 70);
    printf("bottom\n");

    return 0;
}

//  void function - this function isn't going to return any information
// parameter is a value we give to a function
void sayHi(char name[], int age){
    printf("Hello %s, you are %d age\n",  name, age);
}

