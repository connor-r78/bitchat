#include "stdio.h"
#include "utils.h"

bool bit(unsigned char bitfield, int idx)
{
  unsigned char ref = 1 << idx;
  unsigned char tmp = ref & bitfield;
  return ( tmp > 0 );
}

/* WIP
int trainToken(FILE* tokens, int tokenID, int learningRate)
{
  for ( int i = 0;  i < learningRate, ++i ) {
    fseek(tokens, tokenID * WEIGHTS_SIZE + rand() % NUM_WEIGHTS, SEEK_SET)
     
  }

  return 0;
}

int trainWeight(FILE* hiddenlayer, int nodeID, int learningRate)
{
  return 0;
}
*/
