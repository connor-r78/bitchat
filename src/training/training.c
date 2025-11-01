#include <stdio.h>

int main() 
{
  FILE *tokens;
  tokens = fopen("../../tokens.txt", "w");
  
  fprintf(tokens, "hello, world");
  
  return 0;
}