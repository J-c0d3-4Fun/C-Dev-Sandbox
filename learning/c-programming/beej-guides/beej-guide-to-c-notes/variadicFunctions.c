#include <stdio.h>
#include <stdlib.h>


// Variadic Functions
// take arbitrary number of arguments

// Ellipses in Function Signatures
// put all the arguments that must be passed first
// it has to be at least one

// Getting the Extra Arguments
// include <stdarg.h>
// va_list = variable argument list
// start processing arguments with a call to va_start()
// process each argument in turn with va_arg()
// when done wrap it up with va_end()
// when calling va_start() , you need to pass in the last named parameter
// (the one just before the ...)
// when you call va_arg() to get the next argument you 
// have to tell it the type of argument to get next



// va_list Functionality
// va_list is an opaque variable that holds information 
// about which argument we're going to get next with va_arg()


void func(int a,...){
    printf("a is %d\n", a);
}

int main(void){

    func(1,2,3,3,4,5,8,5,6,7,6,9,6,10);
    return 0;
}