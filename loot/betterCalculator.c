#include <stdio.h>
#include <stdlib.h>

// add, subtract, multiply, divide

int main(){

    double num1;
    double num2;
    char op;

    printf("Enter a number: ");
    scanf("%lf", &num1);

    printf("Enter operator: ");
    // put a space befor %c otherwise it wont work
    scanf(" %c", &op);

    printf("Enter a number: ");
    scanf("%lf", &num2);

    if (op == '+') {
        printf("%f", num1 + num2);
    
    }else if (op == '-') {
        printf("%f", num1 - num2);
    
    }else if (op == '/') {
        printf("%f", num1 / num2);
    
    }else if (op == '*') {
        printf("%f", num1 * num2);
    
    }else {
        printf("Invalid operator");
    }

    return 0;
}