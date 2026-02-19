#include <stdio.h>
#include <stdlib.h>

extern int a;

int main(void){
   
printf("%d\n", a);

a = 99;

printf("%d\n", a);


}