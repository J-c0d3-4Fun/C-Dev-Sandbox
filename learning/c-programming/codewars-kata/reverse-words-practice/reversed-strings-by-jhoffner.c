// Problem can be found here:
// https://www.codewars.com/kata/5168bb5dfe9a00b126000018/c


#include <stdio.h>


char *strrev (char *string)
{
  int charcount = 0;

  
  while(string[charcount] != '\0')
    ++charcount;
  
  int size = charcount;
  char temp;
  int begin = 0;
  int end = size - 1;
  
  while(begin < end){
    temp = string[begin];
    string[begin] = string[end];
    string[end] = temp;
    
    
    ++begin;
    --end;
  }
  
  return string; // reverse the string in place and return it
}