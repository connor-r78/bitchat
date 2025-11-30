#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BYTE_SIZE 0x8
#define NUM_TOKENS 456976
#define NUM_WEIGHTS 0x8000

#define TOKENS_SIZE NUM_TOKENS / BYTE_SIZE
#define WEIGHTS_SIZE NUM_WEIGHTS / BYTE_SIZE

extern long _input();
extern long _printToken(long tokenID);

extern char input[0x1000];

bool* parseWeight(unsigned char data)
{ 
  bool* weights = malloc(BYTE_SIZE * sizeof(bool));

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

  int exp = 3;
  for ( int i = tokenOffset; i < 4 + tokenOffset; ++i ) {
    char letter = token[i];
    letter -= 0x41;
    if ( letter < 0 ) letter = 0;
    tmp += letter * pow(26, exp); 
    --exp;
  }

  return tmp;
}

unsigned char* grabTokenData(FILE* tokens, long token)
{
  unsigned char* tmpTokenData = (unsigned char*) malloc(WEIGHTS_SIZE);
  
  long offset = token * 1000;

  fseek(tokens, offset, SEEK_SET);
  fread(tmpTokenData, 1, sizeof tmpTokenData, tokens);

  return tmpTokenData;
}

unsigned char* grabLayerData(FILE* hiddenLayer)
{
  unsigned char* tmpLayerData = (unsigned char*) malloc(TOKENS_SIZE);

  return tmpLayerData;
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
      memcpy(tokenData + i * WEIGHTS_SIZE, newTokenData, WEIGHTS_SIZE);
      free(newTokenData);
    }
  }

  bool* weights = parseWeight(*tokenData);
  free(tokenData); 

  hiddenLayer = fopen("hiddenLayer.txt", "r");

  int layerData[NUM_WEIGHTS];

  for ( int i = 0; i < NUM_WEIGHTS; ++i ) {
    if ( weights[i] ) ++layerData[i];
    else --layerData[i];
  }   

  free(weights);

  return 0;
}
