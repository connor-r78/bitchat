#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_WEIGHTS 0x8000

extern long _input();

extern char input[0x1000];

int* parseWeight(unsigned char data)
{ 
  int* weights = malloc(8 * sizeof(int));

  for ( int i = 7; i >= 0; --i ) {
    double idx = (double) i;
    if ( data >= pow(2.0, idx) ) {
      weights[i] = 1;
      data -= pow(2.0, idx);
    }
    else weights[i] = 0;
  }

  return weights;
}

long calcToken(char* token, int tokenOffset)
{
  tokenOffset *= 4;

  long tmp = 0;

  for ( int i = tokenOffset; i < 4 + tokenOffset; ++i ) {
    char letter = token[i];
    letter -= 0x41;
    if ( letter < 0 ) letter = 0;
    tmp += letter + 26 * i;
  }

  tmp -= 156;

  return tmp;
}

unsigned char* grabTokenData(FILE* tokens, long token)
{
  unsigned char* tmpTokenData = (unsigned char*) malloc(NUM_WEIGHTS / 8);
  
  long offset = token * 1000;

  fseek(tokens, offset, SEEK_SET);
  fread(tmpTokenData, 1, sizeof tmpTokenData, tokens);

  return tmpTokenData;
}

int main()
{
  long chars = _input();
  long numTokens = chars / 4;
  if ( chars % 4 != 0 ) ++numTokens;

  FILE* tokens;
  FILE* hiddenLayer;

  tokens = fopen("tokens.txt", "r");
  unsigned char* tokenData = (unsigned char*) malloc(numTokens * NUM_WEIGHTS);
 
  if ( tokens ) {
    for ( int i = 0; i < numTokens; ++i ) {
      unsigned char* newTokenData = grabTokenData(tokens, calcToken(input, i));
      memcpy(tokenData + i * NUM_WEIGHTS / 8, newTokenData, NUM_WEIGHTS / 8);
      free(newTokenData);
    }
  }

  int* weights = parseWeight(*tokenData);
  printf("%c or %b\n", *tokenData, *tokenData);
  for ( int i = 0; i < 8; ++i ) {
    printf("%d: %d\n", i, weights[i]);
  }
  free(weights);

  hiddenLayer = fopen("hiddenLayer.txt", "r");

  free(tokenData);

  return 0;
}
