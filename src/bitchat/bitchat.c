#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BINARY_BASE 2.0

#define ALPHA_LEN 0x1A
#define BYTE_SIZE 0x8
#define MAX_INPUT 0x1000
#define NUM_TOKENS 456976
#define NUM_WEIGHTS 0x1000
#define TOKEN_SIZE 0x4

#define TOKENS_SIZE NUM_TOKENS / BYTE_SIZE
#define WEIGHTS_SIZE NUM_WEIGHTS / BYTE_SIZE

extern long _input();
extern long _printToken(long tokenID);

extern char input[MAX_INPUT];

bool* parseWeight(unsigned char data)
{ 
  bool* weights = malloc(BYTE_SIZE * sizeof(bool));

  for ( int i = BYTE_SIZE - 1; i >= 0; --i ) {
    double idx = (double) i;
    if ( data >= pow(BINARY_BASE, idx) ) {
      weights[i] = true;
      data -= pow(BINARY_BASE, idx);
    }
    else weights[i] = false;
  }

  return weights;
}

long calcToken(char* token, int tokenOffset)
{
  tokenOffset *= TOKEN_SIZE;

  long tmp = 0;

  int exp = TOKEN_SIZE - 1;
  for ( int i = tokenOffset; i < TOKEN_SIZE + tokenOffset; ++i ) {
    char letter = token[i];
    letter -= 'A';
    if ( letter < 0 ) letter = 0;
    tmp += letter * pow(ALPHA_LEN, exp); 
    --exp;
  }

  return tmp;
}

unsigned char* grabTokenData(FILE* tokens, long token)
{
  unsigned char* tmpTokenData = (unsigned char*) malloc(WEIGHTS_SIZE);
  
  long offset = token * TOKEN_SIZE;

  fseek(tokens, offset, SEEK_SET);
  fread(tmpTokenData, 1, sizeof tmpTokenData, tokens);

  return tmpTokenData;
}

unsigned char* grabLayerData(FILE* hiddenLayer, long node)
{
  unsigned char* tmpLayerData = (unsigned char*) malloc(TOKENS_SIZE);

  long offset = node * TOKENS_SIZE;

  fseek(hiddenLayer, offset, SEEK_SET);
  fread(tmpLayerData, 1, sizeof tmpLayerData, hiddenLayer);

  return tmpLayerData;
}

int updateLayer(bool* layer, int* tokens, int numTokens)
{
  for ( int i = 0; i < numTokens; ++i ) {
    layer[tokens[i]] = 1;
  }

  return 0;
}

int* findActivated(unsigned char* data, size_t dataSize, int* numActivated)
{
  size_t totalActivated = 0;

  size_t i = 0;
  uint64_t chunk;
  for (; i + BYTE_SIZE <= dataSize; i += BYTE_SIZE) {
    memcpy(&chunk, data + i, BYTE_SIZE);
    totalActivated += __builtin_popcountll(chunk); 
  }

  for (; i < dataSize; i++) totalActivated += __builtin_popcount(chunk);

  int* activated = (int*) malloc(totalActivated * sizeof(int));

  int idx = 0;
  for ( int i = 0; i < TOKENS_SIZE; ++i ) {
    bool* weights = parseWeight(data[i]);

    for ( int j = 0; j < BYTE_SIZE; ++j ) {
      if ( weights[j] ) activated[idx] = i * BYTE_SIZE + j;
      ++idx;
    }

    free(weights);
  }

  *numActivated = idx;

  bool* layerData = (bool*) malloc(TOKENS_SIZE);

  for ( int i = 0; i < NUM_WEIGHTS; ++i ) {
    unsigned char* newLayerData = grabLayerData(hiddenLayer, i);

    int numActivatedTokens = 0;
    int* numActivatedTokensPtr = &numActivatedTokens;
    int* activatedTokens = findActivated(
      newLayerData,
      (size_t) TOKENS_SIZE, 
      numActivatedTokensPtr
    );

    for ( int i = 0; i < WEIGHTS_SIZE; ++i ) 
      updateLayer(layerData, activated, idx);

    free(activatedTokens);
  }   
}

int main()
{
  long chars = _input();
  long numTokens = chars / TOKEN_SIZE;
  if ( chars % TOKEN_SIZE != 0 ) ++numTokens;

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

  hiddenLayer = fopen("hiddenlayer.txt", "r");


  free(layerData);
  free(weights);
}
