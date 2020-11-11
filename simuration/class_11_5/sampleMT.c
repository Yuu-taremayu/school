#include <stdio.h>
#include "MT.h"

#define NUM 10

int main(void)
{
  int i;
  int seed;

  seed = 0;
  init_genrand(seed);

  for (i=0;i<NUM;i++) {
    printf("%ld\n",genrand_int32());
  }
  printf("\n");

  for (i=0;i<NUM;i++) {
    printf("%lf\n",genrand_real1());
  }
  printf("\n");

  return 0;
}
