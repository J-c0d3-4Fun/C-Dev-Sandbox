#include <stdio.h>
#include <stdlib.h>

int main(){

    // create. apointer to a physical file on the machine
    // fopen(file, filemode) r - read w - write a - append

    FILE * fpointer = fopen("employees.txt", "w");

    // allows us to write information to a file
    fprintf(fpointer, "Jim, Salesman\nPam, Receptionist\nOscar, Accounting");

    // anytime you open a file you must close it like a stream
    fclose(fpointer);

    // append

    FILE * fpointer2 = fopen("employees.txt", "a");

    // allows us to write information to a file
    fprintf(fpointer2, "\nKelly, Customer Service");

    // anytime you open a file you must close it like a stream
    fclose(fpointer);


    return 0;
}