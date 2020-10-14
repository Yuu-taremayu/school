#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_ARRAY_SIZE (1LL << 10)
#define MAX_ARRAY_SIZE (1LL << 35)

/* アクセスする配列 */
char __attribute__ ((aligned(64))) a[MAX_ARRAY_SIZE];

double write_random(char *a,long long int size, long long int count);

int main(int argc,char **argv)
{
  long long int size;
  double t;
  
  printf("size(KB)\ttime(s)\n");
  for (size = MIN_ARRAY_SIZE;size <= MAX_ARRAY_SIZE;size <<= 1){
    t = write_random(a,size,1024LL * 1024 * 100);
    printf("%10.2f\t%4.2f\n",(double)size / (1 << 10),t);
  }
}

double write_random(char *a,long long int size, long long int count)
{
  long long int i;
  struct timespec ts,te;

  clock_gettime(CLOCK_REALTIME, &ts);
  for (i = 0;i < count;i++){
    /* 配列のどこかのバイトをカウントアップする */
    a[random() % size]++;
  }
  clock_gettime(CLOCK_REALTIME, &te);
  return ((double)(te.tv_sec - ts.tv_sec) + (double)(te.tv_nsec - ts.tv_nsec) / (1000 * 1000 * 1000));
}

