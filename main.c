#include <stdio.h>

#define TOKEN_DATA_SIZE 128*531441

extern long _input(char* ptr);

int main()
{
  FILE *tokens;
  FILE *hiddenLayer;

  tokens = fopen("tokens.txt", "r");
  char tokendata[4096];
  fgets(tokendata, 4096, tokens);

  hiddenLayer = fopen("hiddenLayer.txt", "r");

  _input(tokendata);
  
  return 0;
}
