// Rewrite the temperature conversion program of 
// Section 1.2 to use a function for conversions

#include <stdio.h>

float conversion(int fahr);

int main(){
    int fahr, celsius = 0;
    int lower,upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celsius = conversion(fahr);
        printf("%3.0f t%6.1f\n", fahr, celsius);
        fahr = fahr + step;
        
    }

    
    
}



float conversion(int fahr) {
     float celsius = (5.0/9.0) * (fahr-32.0);
     return  celsius;
}