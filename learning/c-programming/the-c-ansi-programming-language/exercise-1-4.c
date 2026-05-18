// Write a program to print the corresponding Celsius to Fahrenheit table


/*
Research:
(32°F − 32) × 5/9 = 0°C

*/ 

#include <stdio.h>

int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    celsius = lower;

    printf("Celsius-Farenheit Table\n");
    printf("-----------------------\n");

    while (celsius <= upper) {
        fahr = (9.0/5.0) * celsius + 32;
        printf("%3.0f %6.1f\n", celsius, fahr);
        celsius = celsius + step;
    }

}