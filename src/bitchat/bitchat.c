#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "../bitchat.h"
#include "../utils/utils.h"

#define BINARY_BASE 2.0

#define ALPHA_LEN 0x1A
#define BYTE_SIZE 0x8
#define MAX_INPUT 0x1000
#define NUM_TOKENS 456976
#define NUM_WEIGHTS 0xF0000
#define TOKEN_SIZE 0x4

#define TOKENS_SIZE NUM_TOKENS / BYTE_SIZE
#define WEIGHTS_SIZE NUM_WEIGHTS / BYTE_SIZE

int wrapToken(char* token)
{
  int ret = 0;
  for ( int i = 0; i < 4; ++i ) {
    ret += ( token[i] - 'A' ) * pow(26, i);
  }

  return ret;
}

char* unwrapToken(int token)
{
  char* ret = (char*) malloc(sizeof(char) * 4); 

  for ( int i = 0; i < 4; ++i ) {
    char c = token % 26;
    token /= 26;
    c += 'A'; 
    ret[i] = c;
  } 

  return ret;
}

unsigned char* grabTokenData(FILE* tokens, long token)
{
  unsigned char* tmpTokenData = (unsigned char*) malloc(WEIGHTS_SIZE);
  
  long offset = token * WEIGHTS_SIZE;

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

char* bitchat(char* input, int seed)
{
  if ( seed == 0 ) {
    struct timeval start;
    gettimeofday(&start, NULL); 
    srand(start.tv_sec);
  }
  else srand(seed);

  int chars = strlen(input);
  int numTokens = strlen(input) / TOKEN_SIZE;
  if ( chars % TOKEN_SIZE != 0 ) ++numTokens;

  FILE* tokens;
  FILE* hiddenLayer;

  tokens = fopen("data/tokens.txt", "r");
  int tokenDataLen = numTokens * WEIGHTS_SIZE;
  unsigned char* tokenData = (unsigned char*) malloc(tokenDataLen);
 
  if ( tokens ) {
    for ( int i = 0; i < numTokens; ++i ) {
      unsigned char* newTokenData = grabTokenData(tokens, i);
      if ( i == 0 ) *tokenData |= *newTokenData;
      else *tokenData &= *newTokenData; 
      free(newTokenData);
    }
  }

  int numnodes = 0;
  int* numnodesptr = &numnodes;
  int* nodes = markNodes(tokenData, numnodesptr);
  free(tokenData); 

  hiddenLayer = fopen("data/hiddenlayer.txt", "r");

  int* activated = malloc(NUM_TOKENS * sizeof(int));

  for ( int i = 0; i < numnodes; ++i ) 
    activate(hiddenLayer, nodes[i], activated);
  free(nodes);

  int outputID = activated[rand() % NUM_TOKENS];
  free(activated);

  return unwrapToken(outputID);
}
