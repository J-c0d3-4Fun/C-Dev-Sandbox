#include <stdio.h>
#include <stdlib.h>


// Type Qualifiers for Arrays in Parameter Lists
// p[] = *p 
// using array notation
// it goes in the brackets, and you can put the optional count after
 int func(int *const volatile p );
 int func(int p[const volatile]);
 int func(int p[const volatile 10]);

//  static for Arrays in Parameters Lists
// always followed by a dimension
int func(int p[static 4]);
// the compiler is going to assume that any you pass to 
// the function will be at least 4 elements
// this basically sets the minimum size array you can have

// Equivalent Initializers 
// C is flexible when it comes to array initializers
// if parts of initializer is left ogg, the compiler sets
// the corresponding elements to 0

int main(void){
    int g[3][2] ={
        {1,2},
        {4,5},
        {3,6}
    };

    for (int row = 0; row < 3; row++ ){
        for (int col = 0; col < 2; col++){
            printf("%d", g[row][col]);
        };

    };

    int a[] = {11, 22, 33, 55};
    int b[] = {12, 23};
    func(a);
    func(b); // <- not enough elements int the array

    return 0;
}