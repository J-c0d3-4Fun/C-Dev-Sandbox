#include <stdio.h>
#include <stdlib.h>


// using the sizeof to get the number of bytes to allocate

// malloc()
// accepts a number of bytes to allocate, 
// returns a void pointer to that block of newly allocated memory
// use the sizeof() and pass it to malloc()
// free() to deallocate that memory for future use

// calloc()
// 1. similar to malloc , with two key differences
// instead of a single argument, you pass the size of one element
// and the number of elements you wish to allocate <- best for arrays!
// 2. it also clears the memory to zero
// NOTE: you still use free() to deallocate any memory obtained through calloc()


// realloc() <- this will be useful for reading files/data >; )
// takes a pointer to some previously-allocated memory by (malloc() or calloc())
// and a new size for the memory region to be
// grows and shrinks memory and returns a pointer to it.
// NOTE IMPORTANT!: sometimes it might return the same pointer
// (this is if the data didn't have to be copied elsewhere)
//  or it might return a different one (if the data did have to be copied)
// NOTE IMPORTANT!: when calling realloc(), you specify the number of BYTES (bytes)
// to allocate, and not just the number of array elements
// NOTE IMPORTANT!: 
// 1. can be used to grow a buffer as we read more data
// 2. can be used to shrink the buffer down to the perfect size 
// after we've completed the read

int main(){

    int *p = malloc(sizeof(int));
    // can also use the pointer as argument as it is a pointer of type <whatever you declare> 
    // in this example pointer to type int so we get the sizeof(int)
    int *t = malloc(sizeof(t));

    *p = 12;
    printf("%d\n", *p);
    free(p);

    // allocating 1456 bytes of memory for an array
    // NOTE IMPORTANT!: no initialization done on the newly allocated memory
    // that means its full of garbage, clear it using memset() or calloc()
    char *s = malloc(1456);


    // Allocate space for 10 ints with calloc, initialized to 0:
    // remember with malloc() you have to manually set the memory to 0 via memset() or calloc()
    int *c = calloc(10, sizeof(int));
   

    int *x;
    // Always check for errors!
    if ((x = malloc(sizeof(int) * 10)) == NULL){
        printf("Error allocating %zu of type int", sizeof(int) * 10 );
    }

    // reallocating array to hold 20 elements instead of 10s
    int *new_t = realloc(t, sizeof(t) * 20);
    // Check for errors!
    if (new_t == NULL){
        printf("Error reallocating memory\n");
        return 1;
    }
    // if no errors reassign t to point to the newly allocated memory
    t = new_t;

    free(t);

    // these two lines are eqivalent
    // convenient if you dont want to special case malloc 

    // char *y = malloc(3490);
    // char *y = realloc(NULL, 3490);
  
}