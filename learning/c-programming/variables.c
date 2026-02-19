#include <stdio.h>
#include <stdlib.h>

int main()
{
    // variables are containers 
    char characterName[] = "George";
    int characterAge = 70;

    // %s allows us to input a string variable , in this case characterName
    printf("There once was a man named %s\n", characterName);
    
    // %d allows us to input a integer, in this case characterAge
    printf("he was %d years old.\n", characterAge);

    // modifying the variable 
    characterAge = 31;
    printf("He really liked the name %s\n", characterName);
    printf("but did not like being %d. \n", characterAge);

    return 0;

}