// Problem found below
// https://www.codewars.com/kata/53da6d8d112bd1a0dc00008b/c


#include <stdlib.h>

// return a dynamically allocated int array
// return array will be freed by the tester

int *reverse_list(const int *array, size_t length) {
    
    size_t i;
    int* array2 = malloc(length * sizeof(int));
    
    for(i = 0; i < length; ++i )
      array2[i] = array[i];
  
    int begin = 0;
    int end = length - 1;
    int temp;
  
    while(begin < end){
      temp = array2[begin];
      array2[begin] = array2[end];
      array2[end] = temp;
      
      ++begin;
      --end;
    }
    
    return array2;

    
  
    //  <---  hajime!

}