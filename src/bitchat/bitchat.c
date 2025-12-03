#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BINARY_BASE 2.0

#define ALPHA_LEN 0x1A
#define BYTE_SIZE 0x8
#define MAX_INPUT 0x1000
#define NUM_TOKENS 456976
#define NUM_WEIGHTS 0x1000
#define TOKEN_SIZE 0x4

#define TOKENS_SIZE NUM_TOKENS / BYTE_SIZE
#define WEIGHTS_SIZE NUM_WEIGHTS / BYTE_SIZE

#include "../utils/utils.h"

extern long _input();
extern long _printName();
extern long _printToken(long tokenID);

extern char input[MAX_INPUT];

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
  fread(tmpLayerData, 1, TOKENS_SIZE, hiddenLayer);

  return tmpLayerData;
}

int updateLayer(bool* layer, int* tokens, int numTokens)
{
  for ( int i = 0; i < numTokens; ++i ) {
    layer[tokens[i]] = 1;
  }

  return 0;
}

int append(int* array, int data, int* idx)
{
  array[*idx] = data;

  ++*idx;
  return 0;
}

int activate(FILE* hiddenlayer, int node, int* activated)
{
  unsigned char* layerData = grabLayerData(hiddenlayer, (long) node);

  for ( int i = 0; i < TOKENS_SIZE; ++i ) {
    unsigned char bits = layerData[i];
    for ( int j = 0; j < BYTE_SIZE; ++j ) {
      int tokenID = i * BYTE_SIZE + j;
      if ( bit(bits, j) ) append(activated, tokenID, &tokenID); 
    }
  }

  return 0;
}

int* markNodes(unsigned char* tokenData, int* nodes)
{
  *nodes = 0;
 
  int* tmp = (int*) malloc(NUM_WEIGHTS * sizeof(int));

  for ( int i = 0; i < WEIGHTS_SIZE; ++i ) {
    unsigned char bits = tokenData[i];
    for ( int j = 0; j < BYTE_SIZE; ++j ) {
      if ( bit(bits, j) ) append(tmp, i * BYTE_SIZE + j, nodes);
    }
  }

  int* newtmp = (int*) malloc(*nodes * sizeof(int));

  for ( int i = 0; i < *nodes; ++i ) {
    newtmp[i] = tmp[i];
  }

  free(tmp);
  return newtmp;  
}

int main()
{
  srand(time(NULL));

  long chars = _input();
  long numTokens = chars / TOKEN_SIZE;
  if ( chars % TOKEN_SIZE != 0 ) ++numTokens;

  FILE* tokens;
  FILE* hiddenLayer;

  tokens = fopen("tokens.txt", "r");
  int tokenDataLen = numTokens * WEIGHTS_SIZE;
  unsigned char* tokenData = (unsigned char*) malloc(tokenDataLen);
 
  if ( tokens ) {
    for ( int i = 0; i < numTokens; ++i ) {
      unsigned char* newTokenData = grabTokenData(tokens, calcToken(input, i));
      if ( i == 0 ) *tokenData |= *newTokenData;
      else *tokenData &= *newTokenData; 
      free(newTokenData);
    }
  }

  int numnodes = 0;
  int* numnodesptr = &numnodes;
  int* nodes = markNodes(tokenData, numnodesptr);
  free(tokenData); 

  hiddenLayer = fopen("hiddenlayer.txt", "r");

  int* activated = malloc(NUM_TOKENS * sizeof(int));

  for ( int i = 0; i < numnodes; ++i ) {
    activate(hiddenLayer, nodes[i], activated);
  }
  free(nodes);

  long outputID = (long) activated[rand() % NUM_TOKENS];
  _printName();
  _printToken(outputID);

  free(activated);
}
