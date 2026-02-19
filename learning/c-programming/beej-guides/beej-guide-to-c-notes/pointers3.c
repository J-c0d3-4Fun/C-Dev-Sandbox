#include <stdio.h>
#include <stdlib.h>


// pointers and pointers to pointers
// you can pointer to anything with & (including to a pointer!)
// You can get the thing a pointer points to with * (including a pointer!)
// thing of & as being used to make pointers and *
// being the inverse

// Multibyte Values
// you can tell which address in memory is the first byte of the 
// object by using the standard & operator
// which always returns the addres of the first byte

// if you iterate over the bytes of any object
// you get its object representation

// These things can be used interchangeably:
// NULL
// 0
// '\0'
// (void *)0

// Pointers to Functions
// float (*p)(int,int); 
// 
// 
void print_int(int n){
    printf("%d\n", n);
};

int main(void){

int x = 3490;
int *p = &x;
int **q = &p;


printf("%d", **q);

// assign j to point to print_int

void (*j)(int) = print_int;
j(5679);
    return 0;
}