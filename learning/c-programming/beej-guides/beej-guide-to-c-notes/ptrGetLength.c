#include <stdio.h>
#include <stdlib.h>


int strLength( char *t){
    char *p = t;
    while (*p != '\0') {
        p++;
    }
    return p - t;
}


int main(){

    char s[] = "Hey Lets try this with pointers!";
    

    printf("string length = %d",strLength(s));
    return 0;
}