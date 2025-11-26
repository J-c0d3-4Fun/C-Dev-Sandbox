
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// If you have a pointer to a type, adding one to the pointer moves 
// to the next item of that type directly after it in memory 
// create a movable cursor into the array >: )

int a[] = { 23, 56,78,32,55, 999};

int *p = &a[0];



int main(){
    // dereferences the pointer 
    // p ← reference to → memory address &a[0] dereferencing → gives actual value stored there
    // **p -> &a[0]
    printf("%d\n", *p);
    // lets move to the next memory address
    printf("%d\n", *(p + 1));
    
    
    // using a for loop
    unsigned int i;
    for (i = 0 ; i < 5; i++) {
        printf("%d\n", *(p+i));
    }

    // changing pointers using a while loop
    while (*p != 999) {
        printf("%d\n", *p);
        p++;
    }




}

//  C knows that p is a. pointer to an int. It knows the sizeof an int
// and it knows how to skip that many bytes to get to the next int.
// tells the program jump sizeof(type) <- this gets you the bytes of the type

// fundamental formula of array/pointer equivalence 
// a[b] == *(a + b)
// Use pointer or array notion to access elements 
// can use *p or p[]


