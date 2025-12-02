#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#define ARGS 0x2

#define INVALID_USAGE -0x1

#define BYTE_SIZE 0x8
#define NUM_TOKENS 456976 
#define NUM_WEIGHTS 0x1000

#define TOKENS_SIZE NUM_TOKENS / BYTE_SIZE
#define WEIGHTS_SIZE NUM_WEIGHTS / BYTE_SIZE

int calcChar(int bits[]) 
{
  int tmp = 0;

  for ( int i = 0; i < BYTE_SIZE; ++i ) {
    tmp += bits[i] * pow(2, i);
  }

  return tmp;
}

int randChar()
{
  int bits[8];

  for ( int i = 0; i < BYTE_SIZE; ++i ) {
    bits[i] = rand() % 2;
  }

  return calcChar(bits);
}

int layerGen()
{
  FILE* hiddenLayer;
  hiddenLayer = fopen("hiddenlayer.txt", "w");

  for ( int i = 0; i < NUM_WEIGHTS; ++i ) {
    for ( int j = 0; j < TOKENS_SIZE; ++j ) {
      unsigned char add = 0;
      add += randChar();
      fprintf(hiddenLayer, "%c", add);
    }
    printf("%X\n", i);
  }

  return 0;
}

int tokenGen()
{
  FILE* tokens;
  tokens = fopen("tokens.txt", "w");

  for ( int i = 0; i < NUM_TOKENS; ++i ) {
    for ( int j = 0; j < WEIGHTS_SIZE; ++j ) {
      unsigned char add = 0;
      add += randChar();
      fprintf(tokens, "%c", add);
    }
    printf("%X\n", i); 
  }

  return 0;
}

int print_usage(char* name)
{
  printf("usage: %s [-l] [-t]\n", name);
  return INVALID_USAGE;
}

int main(int argc, char** argv) 
{
  srand(time(NULL));

  int opt;

  if ( argc > ARGS ) return print_usage(argv[0]);

  while ( (opt = getopt(argc, argv, "lt")) != -1 ) {
    switch ( opt ) {
    case 'l':
      return layerGen();
      break;
    case 't':
      return tokenGen();
      break;
    case '?':
      printf("Unknown option: %c\n", optopt);
      print_usage(argv[0]);
    }
  }
}
