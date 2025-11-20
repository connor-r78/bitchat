#include <stdio.h>
#include <stdlib.h>

#define NUM_WEIGHTS 0x1000 

extern long _input();

extern char input[0x1000];

int calcToken( char* token, int tokenOffset )
{
  tokenOffset *= 4;

  int tmp = 0;

  for ( int i = tokenOffset; i < 4 + tokenOffset; i++ ) {
    char letter = token[i];
    letter -= 0x41;
    if ( letter < 0 ) letter = 0;
    tmp += letter + 26 * i;
  }

  return tmp;
}

int main()
{
  _input();

  calcToken(input, 0);

  FILE *tokens;
  FILE *hiddenLayer;

  tokens = fopen("tokens.txt", "r");
  
  if ( tokens ) {
  
    char* tokendata = (char*) malloc(NUM_WEIGHTS);
    fgets(tokendata, NUM_WEIGHTS, tokens);

    printf("%s\n", tokendata); 

    free(tokendata);
 
  } 
 
  hiddenLayer = fopen("hiddenLayer.txt", "r");

  return 0;
}
