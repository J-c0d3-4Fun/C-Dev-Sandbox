#include <stdio.h>
#include <stdlib.h>
#include <string.h>


 struct len_string { int length; char data[];};

 struct len_string *len_string_from_c_string(char *s){

    int len = strlen(s);

    // Allocate "len" more bytes
    struct len_string *ls = malloc(sizeof *ls + len);

    ls->length = len;

    // Copy the string into those extra bytes
    memcpy(ls->data, s, len);




    return 0;
}