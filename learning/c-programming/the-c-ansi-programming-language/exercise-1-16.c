// Revise the main routine of the longest-line program so it 
// will correctly print the length of arbitrarily long input
// and as much as possible of the text


#include <stdio.h>
#define MAXLINE 1000

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);


int main(){

    int len;
    int max;
  
 



    char line[MAXLINE];
    char longest[MAXLINE];


    max = 0;
 


    while ((len = my_getline(line, MAXLINE)) > 0 ) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }

    }
    if (max > 0) {
        printf("%s", longest);

    return 0;


    }


}

int my_getline(char s[], int lim){
        int c,i, sc;
        i = 0;
        for (sc = 0; (c = getchar()) != EOF && c != '\n'; ++sc) {
            if(i < lim - 1){
                s[i] = c;
                ++i;
            }
              
            
        }
        

        if (c == '\n'){
            s[i] = c;
            ++i;
        
        }
        

        s[i] = '\0';
        return sc;


}

void copy(char to[], char from[]){
    int i;


    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}