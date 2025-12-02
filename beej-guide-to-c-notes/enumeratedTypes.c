#include <stdio.h>
#include <stdlib.h>



// enum
// can only be integer types
// often shown by their symbolic identifier name in a debugger

// vs

// #define
// can define anything at all
// numbers just show as raw numbers which 
// are harder to knw the meaning of while debugging
// 

// Behavior of enum

// Numbering
// automatically numbered unless you override them 
// (start at 0 and autoincrement)

// Trailing Commas
// perfectly fine to do

// Style
// common to declare the enum symbols in uppercase (with underscores)

// REMEMBER !
// enum is a type, analogous to how a struct is a type
// you can give them a tag name 
// C (unlike C++) doesn't actually enforce any 
// values being in range for a particular enum
//  can be typedef'd
// can declare variables when you declare the enum

 enum thisIsAtest{
    TEST6,
    TEST5,
} i = TEST5, m = TEST6;

 enum {
    TEST2,
    TEST3,
} j = TEST2, k = TEST3;

typedef enum{
    TEST,
}a ;


enum resource {
    HORSE,
    GOAT,
    PIG,

};

enum{
    SNAKE = 0, // 0
    DEER, // 1
    DOG = 4, 
    CAT, // 5
    BIRD, // 6
    WOOD, // 7
};

enum{
    ONE=1,
    TWO=2
};


int main(){

    printf("%d %d", ONE, TWO);

    enum resource r = HORSE;

    if (r == HORSE){
        printf("I love this new hours i jut bought!")
    };

    return 0;
}