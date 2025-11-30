#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BYTE_SIZE 0x8
#define NUM_TOKENS 456976; 
#define WEIGHTS 0x1000

int calcChar(int bits[]) 
{
  int tmp = 0;

  for ( int i = 0; i < BYTE_SIZE; ++i ) {
    tmp += bits[i] * pow(2, i);
  }

  return tmp;
}

int randChar() {
  int bits[8];

  for ( int i = 0; i < BYTE_SIZE; ++i ) {
    bits[i] = rand() % 2;
  }

  return calcChar(bits);
}

int main() 
{
  srand(time(NULL));

  FILE *tokens;
  tokens = fopen("tokens.txt", "w");
  for ( int i = 0; i < 0x6F910; ++i ) {
    for ( int j = 0; j < WEIGHTS / BYTE_SIZE; ++j ) {
      char add = 0;
      add += randChar();
      fprintf(tokens, "%c", add);
    }
    printf("%X\n", i); 
  }
  
  return 0;
}
