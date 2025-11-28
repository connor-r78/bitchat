#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_WEIGHTS 0x8000

extern long _input();

extern char input[0x1000];

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

char* grabTokenData(FILE* tokens, long token)
{
  char* tmpTokenData = (char*) malloc(NUM_WEIGHTS / 8);
  
  long offset = token * 1000;

  fseek(tokens, offset, SEEK_SET);
  fgets(tmpTokenData, NUM_WEIGHTS / 8, tokens);

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
  char* tokenData = (char*) malloc(numTokens * NUM_WEIGHTS);
 
  if ( tokens ) {
    for ( int i = 0; i < numTokens; ++i ) {
      char* newTokenData = grabTokenData(tokens, calcToken(input, i));
      printf("%s\n", newTokenData);
      strcat(tokenData, newTokenData);
      free(newTokenData);
    }
  }

  hiddenLayer = fopen("hiddenLayer.txt", "r");

  free(tokenData);

  return 0;
}
