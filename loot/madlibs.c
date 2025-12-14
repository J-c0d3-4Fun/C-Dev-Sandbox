#include <stdio.h>
#include <stdlib.h>

int main ()
{
    char color[10];
    char pluralNoun[20];
    char celebrityF[20];
    char celebrityL[20];

    printf("Enter a color: ");
    scanf("%s", color);

    printf("Enter a pluralNoun: ");
    scanf("%s", pluralNoun);

    printf("Enter a celebrity: ");
    // only grab characters up to the next white space
    scanf("%s%s", celebrityF,celebrityL); 
    
    printf("Roses are %s\n", color);
    printf("%s are blue\n", pluralNoun);
    printf("I love %s %s\n", celebrityF,celebrityL);

    return 0;
}