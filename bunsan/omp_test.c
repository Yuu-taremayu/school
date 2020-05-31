/* OpenMP プログラムのサンプル       */
/* コンパイルと実行                  */
/*                                   */
/*  $ cc -fopenmp omp_test.c         */
/*  $ time ./a.out                   */
/*                                   */
/*  -fopenmpを忘れるても動くけれど， */
/*  ふつうの C プログラムになる      */
/*  →並列実行されない               */

#include <stdio.h>
#include <omp.h>

#define N 1000000

int main(void)
{
  int  i,l,count0;
  int  a[N];
  
  for (i = 0;i < N;i++) a[i] = i % 100;

  for (l = 0;l < 10000;l++){
    count0 = 0;
    #pragma omp parallel for reduction(+:count0) num_threads(8)
    for(i = 0;i < N;i++){
      if (a[i] == 0) count0++;
    }
  }
  printf("count0:%d\n",count0);
}

