#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


// exit()
// can call it from anywhere in the programs

// Setting up Exit Handlers with atexit()
// you can register functions to be called when a program exits
// you can register multiple handlers and 
// they'll be called in reverse order


// quicker Exits
// similar to normal exit, except:
// Open files might not be flushed
// Temporary files might not be removed
// atexit() handlers won't be called


// Nuke it from Orbit _Exit()
// Calling _Exit() exits immediately 


// Exiting Sometimes: assert()
// The assert() statement is used to insist 
// that something be true or lese the program will exit.

// Abnormal Exit: abort()
// if something has gone horribly wrong
// and you want to indicate as much to the outside environment
// 


#define PI 3.14159
int main(void){

    assert(PI > 3);


}