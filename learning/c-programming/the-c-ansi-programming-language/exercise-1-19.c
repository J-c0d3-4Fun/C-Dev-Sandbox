// Write a function reverse(s) that reverses the character string s.
// Use it to write a program that reverses its input a line at a time.

#include <stdio.h>


// REVERSE FUNCTION
// reverse any string that its given
// takes an array of characters <- 2 Parameter - the charcter array, length
// 2 variables - character, index
// For loop to loop through array but backwords
// make a comparison with the index being greater than 0
// make the comparison include the check to confirm its not the newline or EOF character


// MAIN FUNCTION
// first read the line 
// compare if it reaches the end of line '\n' or EOF
// if its not the end of the file throw it into the reverse function <- will need a variable (1)
// return the reversed string
// print the string in reverse


#define MAXLINE 1000

void reverse( char s[], int len);
int my_getline( char line[], int maxlength);


int main(){
    int len;
    char line[MAXLINE];



    while (( len = my_getline(line, MAXLINE) )) {
        reverse(line, len);
        printf("%s", line);
    }
   


    return 0;
}

void reverse( char s[], int len ){

    // start from the left
    int begin = 0; 
    // start from the right
    int end = len - 1;
    char placeholder;


    while (begin < end ) {

        // set the placeholder to be the value of begin
        placeholder = s[begin];
        
        // set the value of begin to be the end value
        s[begin] = s[end];
        // set the end value to be temporary variable
        s[end] = placeholder;

        // increment and decrement 
        ++begin;
        --end;

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