#include <stdio.h>

#define TOKEN_DATA_SIZE 128*531441

extern long _input();

extern char input[0x1000];

int main()
{
  _input();

  printf("%s", input);

  FILE *tokens;
  FILE *hiddenLayer;

  tokens = fopen("tokens.txt", "r");
  char tokendata[4096];
  fgets(tokendata, 4096, tokens);

  hiddenLayer = fopen("hiddenLayer.txt", "r");

  return 0;
}
