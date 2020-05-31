#include <stdio.h>
#include <omp.h>

int main(void)
{
  int a = 1, b = 2, c = 3, d = 4, x, y, z;

  #pragma omp parallel sections
  {
    #pragma omp section
    {
      printf("my thread num=%d\n",omp_get_thread_num());
      x = a + b;
    }
    #pragma omp section
    {
      printf("my thread num=%d\n",omp_get_thread_num());
      y = c + d;
    }
  }
  z = x * y;
  printf("z=%d\n",z);
}
		
