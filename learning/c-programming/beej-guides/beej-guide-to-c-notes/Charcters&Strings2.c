#include <stdio.h>
#include <stdlib.h>



// Escape Sequences
// backslash character (\) followed by another character
// two (or more) characters together have a special meaning

// Single Line Status Updates
// can use the non-standard POSIX function sleep()
// fflush() - forces output to happen RIGHT NOW

// Numeric Escapes
// octal or hexadecimal representation of a byte 
// Unicode
// you can use the escapes \u (16-bit) or \U (32-bit)
// 



int main(){

    printf("A\102C\n");  // 102 is 'B' in ASCII/UTF-8
    printf("\xE2\x80\xA2 Bullet 1\n"); // <-- crummy way to represent unicode
    printf("\u2022 Bullet 1\n");





    return 0;
}