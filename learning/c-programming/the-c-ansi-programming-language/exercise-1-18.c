// Write a program to remove trailing blanks and tabs from 
// each line of input, and to delete entirely blank lines

#define MAXLINE 1000

#include <stdio.h>

int my_getline(char line[], int maxlength );


int main(){
    int i, c;
    int len;
    char line[MAXLINE];

    while ((len = my_getline(line, MAXLINE))) {
        for (i = len - 1; i > 0; --i) {
            if( line[i] != ' ' && line[i] != '\t'){
                break;
                
            }
        }
        line[i + 1] = '\0';

        if(i >= 0)
            printf("%s", line);

    }
    

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