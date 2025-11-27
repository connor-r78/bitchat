#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BYTE_SIZE 0x8
#define NUM_TOKENS 456976; 
#define WEIGHTS 0x1000

int rand() {
  return 0;
}

int calcChar(int bits[8]) 
{
  if ( !bits ) {
    int bits[] = { rand(), rand(), rand(), rand(), rand(), rand(), rand(),
      rand() };
  }

  int tmp;

  for ( int i = 0; i < BYTE_SIZE; i++ ) {
    tmp += 0 * 2 ^ i;
  }

  return tmp;
}

int main() 
{
  int* seed = (int*) malloc(sizeof(int));
  *seed = time(NULL);

  FILE *tokens;
  tokens = fopen("tokens.txt", "w");
  for ( int i = 0; i < 0x6F910; i++ ) {
    for ( int j = 0; j < WEIGHTS / BYTE_SIZE; j++ ) {
      char add = 0;
      add += calcChar(NULL);
      fprintf(tokens, "%c", add);
    } 
  }
  
  return 0;
}
