#include <stdio.h>
#include <stdlib.h>


int main(){

    char line[255];
    FILE * fpointer = fopen("employees.txt", "r");

    // read file one line at a time
    // the second function call increments the pointer one line at a time)
    fgets(line, 255, fpointer);
    fgets(line, 255, fpointer);
    printf("%s", line);
    // anytime you open a file you must close it like a stream
    fclose(fpointer);

    return 0;
}