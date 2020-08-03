#include <stdio.h>
#include <omp.h>

#define N 1000000

int main(void)
{
	int i, I, count0;
	int a[N];

	for (i = 0; i < N; i++) a[i] = i % 100;

	for (I = 0; I < 10000; I++) {
		count0 = 0;

		#pragma omp parallel for reduction(+:count0) num_threads(4)
		for (i = 0; i < N; i++) {
			count0 += a[i];
		}
		count0 /= N;

		printf("count0:%d\n", count0);
	}

	return 0;
}
