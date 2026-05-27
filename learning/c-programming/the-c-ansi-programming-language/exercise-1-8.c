// Write a program to count blanks, tabs, and newlines


#include <stdio.h>

int main() {

    int c,b, t, nl;

    b = t = nl = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++b;
        }else if (c == '\t') {
            ++t;
        }else if (c == '\n') {
            ++nl;
                }
    }
    printf("blanks: %d\n" ,b);
    printf("tabs: %d\n" ,t);
    printf("newlines: %d\n", nl);

}