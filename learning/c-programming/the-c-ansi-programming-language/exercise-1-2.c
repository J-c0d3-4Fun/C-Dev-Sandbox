// Experiment to find out what happens when printf's argument contains
// \c, where c is some character not isted above


#include <stdio.h>

int main() {
    printf("hello world!\c");
    printf("\q");
    printf("\j");
    
}