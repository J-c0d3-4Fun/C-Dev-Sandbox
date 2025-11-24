
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLength(char *s){

    int count = 0;
    // here we compare the count value to the value of NUL
    while (s[count] != '\0') {
        count++;
    
    }
    return count;

}



int main(){

    printf("Enter in your string to get the length: ");
    char p[255];
    fgets(p,255,stdin);

    printf("The strings length is: %d\n", getLength(p) );
    
    
    return 0;
}

