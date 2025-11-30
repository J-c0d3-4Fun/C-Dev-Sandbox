#include <stdio.h>
#include <stdlib.h>

// Command Line Arguments
// argc & argv
// argc = count/ length of the array




// Exit Status
// apart of the <stdlib.h>
// EXIT_SUCCESS or 0
// EXIT_FAILURE 
// Bash exit codes should be be between 0 and 255


// Environment Variables
// getenv() - returns a pointer to the value string or else NULL
// Unix - putenv(), setenv(), unsetenv()
// Windows - _putenv()
// POSIX - environ <---- apart of <unistd.h>
// extern char **environ;
// getenv() is more portable than environ.

int main(int argc, char *argv[]){

    char *val = getenv("WELCOME_TO_MY_PLAYGROUND");

    int total = 0;
    // the zeroth argument is the name of the executable
    // argc  = the argument count 
    for(int i = 0; i < argc; i++){
        printf("arg %d: %s\n", i, argv[i]);
    }

    if (argc != 3) { 
        printf("usage: mult x y\n");
        return EXIT_FAILURE;
    }


    for (int i = 1; i < argc; i++) {
        int value = atoi(argv[i]);

        total += value;
    }
    
    printf("%d\n", total);

    return 0;
}