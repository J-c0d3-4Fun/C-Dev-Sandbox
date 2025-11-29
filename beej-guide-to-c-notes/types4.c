#include <stdio.h>
#include <stdlib.h>

// const
// most common type qualifier
// cannot modify


// const & pointers
// const up front + type name before asterisk = 
// cant change the thing the pointer points to
// i.e. cost int *p = x;
// const after the asterisk = change what the pointer points to
// i.e. int *const p;

// restrict
// is a hint to the compiler that a particular piece of 
// memory will only be accessed by one pointer and never another.
// no aliasing aof the particular object it pointer points to 
// NOTE: that restrict has no effect if the object pointed to is never written to
// has block scope
// if the restricted pointer points to an array, 
// it only applies to the individual objects in the array


// volatile
// tells the compiler that a value might change behind 
// its back and should be looked up every time
// i.e. where the compiler is looking in memory at an address 
// that continuously updates behind the scenes (a timer)

// Storage-Class Specifiers

// auto
// indicates this object has automatic storage duration
// always initialize all automatic variables before use! (or it collects garbage)

//static
// block scope
// in block scope it will only be initialized one time on 
// program startup, not each time the function is called
// if using multithreaded programs, be sure not 
// to let mutiple threads trample the same variable
// file scope
// the variable isn't visible outside of this particular source file 
// think global but only locally


// extern
// gives us a way to refer to objects in other source files >;)

// register
// hint to the compiler that this variable is 
// frequently-used and should be made as fast as possible to access
// you cannot take the  address of a register (no pointer to memory address)


// _Thread_local 
// make sure each thread gets its own copy of the variable 
// ^^^ helps to prevent race conditions 
// <threads.h> <- useful for controlling this

int main() {

// Both can't modify what it points to
const int *p;
int const *t;
volatile int *h;

//  can modify what it points to becaus the const comes after the asterisk 
int x = 10;
int *const j = &x;
*j = 20;



    return 0;
}