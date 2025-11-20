#include <stdio.h>

#define BYTE_SIZE 0x8
#define WEIGHTS 0x1000

int main() 
{
  FILE *tokens;
  tokens = fopen("tokens.txt", "w");
  
  for ( int i = 0; i < WEIGHTS / BYTE_SIZE; i++ ) {
    char add = 0;

    for ( int j = 0; j < BYTE_SIZE; j++ ) {
      add += 0 * 2 ^ j;      
    }

    fprintf(tokens, "%c", add);
  } 
  
  return 0;
}
