#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

// setjmp 
// bookmark in execution with setjmp

//  longjmp
// jump back to the earlier point in execution 
// where the bookmark is set setjmp()


// env & <setjmp.h>
// env is used to keep the state of <- a variable
// things when setjmp() is called
// then it cn be restored when calling longjmp()
// is of type jmp_buf , an opaque type declared in <setjmp.h>

// The Values of Local Variables
// if you want the values of automatic local variables
// to persist in the function that called setjmp() after 
// a longjmp() happens. you must declare those
// variables to be volatile

jmp_buf env;

int main(void){
    volatile int x = 20;
    if(setjmp(env) == 0){
        x = 30;
    };


    return 0;
}