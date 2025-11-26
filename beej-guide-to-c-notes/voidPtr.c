#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void){

    // void Pointers
    // memcpy() 
    // copies bytes of memory from one pointer to another
    // caveat is those pointers can point to any type 
    // basically think of all objects as bytes no matter the type (i.e. int, char)
    
    char s[] = "I love to eat some food!";
    char t[100];

    // memcpy( destination, source, how many bites to return)
    memcpy(t, s, sizeof(s));
    printf("%s\n", t);

    return 0;
}

// can copy floats,ints, chars, and structs
// The power of void - write functions that dont car about the type
// cannot do:
// - pointer arithmetic on a void*
// - dereference a void*
// - use arrow operator on a void* (since it's also a dereference)
// - usee array notation on a void* (since its also a dereference)
// 


// Convert the void* t another type before you use it




