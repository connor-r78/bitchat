#include <stdio.h>

#define LETTERS 26

void _printToken(long tokenID)
{
  char chars[5];

  int i = 0;
  for ( int num = 456976; num > 0; ) {
    num /= LETTERS;
    chars[i] = 'a' + num % LETTERS;
    ++i;
  }

  printf("%s\n", chars); 
}  
