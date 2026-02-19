#include <stdio.h>
#include <stdlib.h>
#define HELLO "Hello this is my first macro"
#define NO_VALUE
#define CHICKEN
// everywhere you see SQR with some value, replace it wih that value times itself
// will lead to macro expansion if  you try a different operator
// i.e. +, SQR(3 + 4) becomes (3 + 4 * 3 + 4)
// FIX: Add parentheses (x) * (x) ^^ becomes (3 + 4) * (3 + 4) <--- add parentheses everytime!
// safest fix for operators with higher precedence:
// #define SQR(x) ((x) * (x)) <-- this is the correct way 
#define SQR(x) x * x 
#define X(a,b, ...) (10*(a) + 20*(b)), __VA_ARGS__
// Stringify
#define Y(...) #__VA_ARGS__ 
 

// before the program is compiled its actually ran through a phase called preprocessing


// #include
// include other sources in your source
// commonly used with header files
// header files can be split into twi categories: system and local
// builtin , you can use angle brackets "< >" <-- system
// use double quotes to include local files " " <-- local
// can use relative directories "../<some file>"

//  Simple Macros
// an identifier that gets expanded to another piece of code
// before the compiler even sees it.
// Think of it as a placeholder of a value, that 
// gets replaced when the preprocessor sees one of those identifiers
// done by using #define
// don't have a specific type
// can also be created with no value 
// constant values that are effectively global and be used ANY place
// can be used to replace or modify keywords


// Conditional Compilation
// get the preprocessor to decide whether or not to 
// present certain blocks of code to the compiler
// or just remove them entirely before compilation.
// similar to if-else statements
// this decision happens at compile time vs 
// if-else statements that get evaluated at runtime
// #ifdef, #ifndef, #else, #if, #elif, #if defined, #undef
// features of C23: #elifdef, #elifndef


// Built-in Macros
// test and use for conditional compilation 
// assert() macro in <assert.h> uses these to call
// out where in the code the assertion failed


// Macros with Arguments 
// can set them up to take arguments that are substituted in
// can have multiple arguments i.e. #define TRIANGLE_AREA(w,h) (0.5 * (w) * (h))

// Macros with Variable Arguments
// The ... (variadic operator)
// have a variable number of arguments passed to a macro
// when the macro is expanded, all the extra arguments 
// will be in a comma-separated list in the VA_ARGS_ macro, 
// and can be replaced from there


// Stringification
// turn any argument into a string by preceding it 
// with a ' # ' in the replacement text
// i.e. #define STR(x) #x

// Concatenation
// can concatenate two arguments together with ##

// Multiline Macros
// can continue a macro multiple lines if you escape the newline
// with a backslash "\" 

// Assert Macro
// adding asserts to your code is a good way to catch conditions that you
// think shouldn't happen
// it checks a condition, and if it's false, the program bombs out
// telling you the file and line number on which the assertion failed

// #embed Directive & Parameters
// New in C23
// can include bytes of a file as integer constants if you'd typed them in
// powerful way to initialize an array with binary data without
// needing to convert it all to code first <- the preprocessor does it for you 

// The limit() Parameter
// specify a  limit on the number of elements to embed with this parameter

// The if_empty Parameter 
// defines what the embed result should be if the file exists but contains no data

// The prefix() and suffix() Parameters
// this is a way to prepend some data on the embed
// NOTE!: these only affect non-empty data

// The __has_embed() Identifier
// This is a great way to test to see if a particular file is available to be embedded
// also whether or not it's empty
// use it with the #if directive
// Will all return false if any additional parameters are also not supported.
// to test give it a file that you know exists as well as a paremeter 
// you want to test the existence for
// can use the __FILE__ macro (expands the name of the source file that references it)
// ie. #if __has_embed(__FILE__ fmc::frotz(lamp))
// puts("fmc::frotz(lamp) is supported!");
// #else
// puts("fmc::frotz(lamp) is NOT supported!");
// #endif


// Pragma D


int main(void){

    printf("%s", HELLO);

    // check isf NO_VALUE is a defined macro, which it is at the head of the file
    #ifdef NO_VALUE
        printf("This has no value!");
    #else
        printf("You must define NO_VALUE first!");
    #endif
        printf("OK!\n");

    // no longer defined
    #undef CHICKEN

    // Builtin Macros
    printf("This function: %s\n", __func__);
    printf("This file: %s\n", __FILE__);
    

    printf("%d\n", SQR(12));

    printf("%d\n %f\n %s\n %d\n", X(5, 4, 3.14 , "Hello", 12));
    printf("%s\n", Y(1,2,3)); // Prints them as string characters


    return 0;
}