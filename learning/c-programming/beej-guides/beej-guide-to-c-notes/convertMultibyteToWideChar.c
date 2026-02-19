#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <locale.h>


int main(void){


    // Get out of the C locale to one that likely euro symbol
    setlocale(LC_ALL, "");


    char *mbString = "The cost is \u20ac1.23";
    size_t mbLength = strlen(mbString);


    wchar_t wcString[128];

    size_t wcLength = mbstowcs(wcString, mbString, 128);


    printf("multibyte: \"%s\" (%zu bytes)\n", mbString, mbLength);
    printf("wide char: \"%ls\" (%zu characters)\n", wcString, wcLength);




}
