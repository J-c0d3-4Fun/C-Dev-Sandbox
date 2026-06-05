// Write a program to print all input lines that are longer than 80 characters

#define MAXLINE 1000

#include <stdio.h>

int my_getline(char line[], int maxlength );

int main() {

    int len;
    char line[MAXLINE];

    while ((len = my_getline(line, MAXLINE)) > 0) {
        if (len > 80) {
            printf("%s", line);
        }
    }


    return 0;
}

int my_getline(char line[], int maxlength){
    int i,c;
    for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF && c != '\n' ; ++i) {
        line[i] = c;
    }
    if (c == '\n'){
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}