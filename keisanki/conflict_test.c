#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* L3 */
#if 1

/* テストのターゲット */
#define TARGET "L3"

/* キャッシュサイズ */
#define CACHE_SIZE  ((1 << (20)) * 12)

/* 連想度 */
#define WAYS_OF_ASSOC  (12)

/* INTERVAL バイトおきに，同じセットに入る */
#define INTERVAL  (CACHE_SIZE / WAYS_OF_ASSOC)

#endif

/* L2 */
#if 0

#define TARGET "L2"
#define CACHE_SIZE  (1 << (18))
#define WAYS_OF_ASSOC  (4)
#define INTERVAL  (CACHE_SIZE / WAYS_OF_ASSOC)

#endif

/* L1 */
#if 0

#define TARGET "L1"
#define CACHE_SIZE  (1 << (15))
#define WAYS_OF_ASSOC  (8)
#define INTERVAL  (CACHE_SIZE / WAYS_OF_ASSOC)

#endif

/* アクセスする配列 */
#define ARRAY_SIZE (1 << 30)

char __attribute__ ((aligned(64))) a[ARRAY_SIZE];

double write_interval(char *a,int interval,int n_intervals,int n_loop);

int main(int argc,char **argv)
{
  int n_intervals;
  double t;
  int i;

  printf("target:%s interval:%d\n",TARGET,INTERVAL);
  printf("n\ttime(s)\n");
  for (n_intervals = 1;n_intervals <= WAYS_OF_ASSOC * 2;n_intervals++){
    t = write_interval(a,INTERVAL,n_intervals,1024 * 1024 * 500 / n_intervals);
    printf("%2d\t%4.2f\n",n_intervals,t);
  }
}

double write_interval(char *a,int interval,int n_intervals,int n_loop)
{
  int i,j;
  struct timespec ts,te;

  clock_gettime(CLOCK_REALTIME, &ts);
  for (i = 0;i < n_loop;i++){
    for (j = 0;j < n_intervals;j++){
      a[interval * j]++;
    }
  }
  clock_gettime(CLOCK_REALTIME, &te);
  return ((double)(te.tv_sec - ts.tv_sec) + (double)(te.tv_nsec - ts.tv_nsec) / (1000 * 1000 * 1000));
}

