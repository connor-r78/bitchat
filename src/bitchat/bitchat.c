#include <stdio.h>
#include <stdlib.h>

#define TOKEN_DATA_SIZE 68027648

extern long _input();

extern char input[0x1000];

int main()
{
  _input();

  printf("%s", input);

  FILE *tokens;
  FILE *hiddenLayer;

  tokens = fopen("../../tokens.txt", "r");
  char* tokendata = (char*) malloc(TOKEN_DATA_SIZE);
  fgets(tokendata, TOKEN_DATA_SIZE, tokens);
  
  printf("%s", tokendata);

  hiddenLayer = fopen("../../hiddenLayer.txt", "r");

  return 0;
}