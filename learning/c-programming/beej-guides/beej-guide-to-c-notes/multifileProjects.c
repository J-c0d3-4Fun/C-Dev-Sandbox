#include <stdio.h>
#include <stdlib.h>
// can use this instead of prototyping
#include "addsubtract.c"



// Includes and Function Prototypes
// must prototype a function prior to using it in another file

// Dealing with Repeated Includes
// include a preprocessor variable when the first time you #include the file
// include a check to make sure that the variable isn't defined
// make it uppercase and replace the period with an underscore 
// bar.c = BAR_H


// Compiling with Object Files
// can compile C files into intermediate representation called object files.
// ^^^compiled machine code that hasn't been put into an executable yet
// clang -c foo.c produces foo.o (foo.obj for Windows)
// compiling from source to object files is relatively slow
// linking a bunch of object files is relatively fast
// make utility that only rebuilds sources that are newer than their outputs


// prototype from addsubtract.c 
// use this if you dont include header
int add(int, int);
int subtract(int, int);

int main(){
    
    printf("%d\n", add(4, 5));
    printf("%d\n", subtract(6, 3));

    return 0;
}