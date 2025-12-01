#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


// Anonymous struct
// struct with no name
// use with typedef
// NOTE!: 
// can also be
// struct{
// char *name;
// int leg_count, speed;
// } a, b, c;
//  

// Self-Referential struct
// graph-like data structure

// Flexible Array Members
// Old Way
// if the last field of the struct is overflowed with data
// it runs out into space that is preallocated 
// ^^^this is if you use malloc() to create extra space
// i.e. struct len_string *s = malloc(sizeof(*s + 40))
// ^^problem with this way is we can access 
// that data it creates undefined behavior X can't 
// access past the set array size

// New Way
// change the definition to have no size for the array
// struct len_string { int length; char data[];};
// space is then allocated by malloc()ing larger struct leng_string


// Padding Bytes
// NOTE!: C is allowed to add padding bytes within 
// or after a struct as it sees fit

// offsetof
// can measure padding 
// found in the <stddef.h> header file

// Fake OOP
// since the pointer to the struct is the same as apointer to the first
// element of the struct, you can freely cast a pointer to the struct
// to a pointer to the first element
// NOTE!: It must be the first element
// ie. struct parent{int a, b;}; struct child{struct parent super; int c,d;};

// Bit-Fields
// pack bits into larger spaces
// C will only combine adjacent bit-fields
// be specific about the signedness when using bit-fields (signed vs unsigned)
// can have unamed-bit fields
// i.e. struct foo { unsigned char a:2; unsigned char :5;};
// ^^ in this example we reserve 5 bytes

// Zero-Width Unnamed Bit-Fields
// put a unnamed bit-field of width 0 where you want the compiler 
// to start anew with packing bits in a different int
// i.e. struct foo { unsigned int a:2; unsigned int :0; unsigned int b:5; };

// Unions 
// similar to structs except the fields overlap in memory
// a way to reuse the same memory space for different types of data
// non-portably write one union field and read from another <- type punning
// if you have a pointer, you can cast that pointer to any of the types of fields 
// in that union and get the values out that way

// Common Initial Sequences in Unions 
// if you have a union of structs, and all those structs begin with a common
// initial sequence, it's valid to access members of that sequence
// from any of the union members
// i.e.
// struct too {char type; int loudness;}; 
// struct boo{char type; int claws;}; 
// union goo{ struct too ta; struct boo ba;};

// Unions and Unnamed Structs
// can use unnamed strcuts in unions

// Passing and Returning struct and union
// You can pass a struct or union to a function by value (as opposed to a pointer to it)
// a copy of that object to the parameter will be made as if by assignment per usual

union fool {
    int e, f, g, h, o;
    float i, j, k;
    char l , m ,n ;

};

struct cabin_information {
    int window_count;
    int o2level;
};

struct spaceship{
    char *manufacturer;
    struct cabin_information ci;
};

struct foo {
    int a;
    char *b;
    int c;
    float d;

};
int main (void){

    struct spaceship s = {
        .manufacturer="General Products",
        .ci.window_count = 8,
        .ci.o2level = 21

    };

    // can also be written like
    struct spaceship j = {
        .manufacturer="General Products",
        .ci = {
            .o2level = 99,
            .window_count = 5
        }


    };
    
    printf("%s: %d seats, %d%% oxygen\n", s.manufacturer, s.ci.window_count, s.ci.o2level);

    // next is a pointer, this is what allows the whole thing to build.
    struct node{
        int data;
        struct node *next;
    };



    printf("%zu\n", offsetof(struct foo, a));



    return 0;
}