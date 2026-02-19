#include <stdio.h>
#include <stdlib.h>



// Possible Obfuscation technique?
// why? 
// just to make your code as unreasonable as possible! 
// This is possible through aliasing with typedef
typedef int a;

a x = 0;
 



// typedef a struct 

typedef struct tree{
    char *type,*leafColor;
    int numOfBranches;
    
} tree;

// either work
struct tree y;
tree z; 


// anonymous structs - dont require you to name the structure thanks to typedef
typedef struct{
    char *name, *color;
    int numOfLegs;

} animal ;

animal i;

// can also be pointers!
// The author doesn't like the fact it hides p is a pointer
// This works perfectly for my case , the more abstract the better
typedef int *newPtr ;
int u = 25;
newPtr p = &u;

// Arrays can also be typedef!
// Once again hiding the true nature of the variable which is exactly what I want
typedef int t[6];

t b = {8, 25, 24, 97, 32};