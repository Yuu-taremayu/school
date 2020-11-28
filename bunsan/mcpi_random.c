/*

円周率を計算する OpenMP プログラム(富士通のパンフレットから引用)

○x86-64 のコードを生成

% cc -fopenmp -O3 mcpi_random.c -o mcpi_random

*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 10000000

int main(int argc,char **argv)
{
  int i,c,nt;
  double x,y;
  double ts,te;
  
  srandom(100);

  for (nt = 1 ;nt <= omp_get_max_threads();nt++){
    c = 0;
    ts = omp_get_wtime();
    #pragma omp parallel for private(x,y) reduction(+:c) num_threads(nt)
    for (i = 0;i < N;i++){
      x = ((double)random()) / (RAND_MAX);
      y = ((double)random()) / (RAND_MAX);
      if (x * x + y * y < 1.0){
	c++;
      }
    }
    te = omp_get_wtime();
    printf("nt=%d time=%f pi=%f\n", nt, te - ts, c * 4.0 / N);
  }
}
