#include <stdio.h>
#include <stdlib.h>

#define NUM_WEIGHTS 0x1000 

extern long _input();

extern char input[0x1000];

int main()
{
  _input();

  printf("%s", input);

  FILE *tokens;
  FILE *hiddenLayer;

  tokens = fopen("../../tokens.txt", "r");
  
  if ( tokens ) {
  
    char* tokendata = (char*) malloc(NUM_WEIGHTS);
    fgets(tokendata, NUM_WEIGHTS, tokens);

    printf("%s\n", tokendata); 

    free(tokendata);
 
  } 
 
  hiddenLayer = fopen("../../hiddenLayer.txt", "r");

  return 0;
}
