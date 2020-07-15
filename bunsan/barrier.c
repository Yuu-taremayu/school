#include <stdio.h>
#include <time.h>
#include <omp.h>

int main(void)
{
	int i, s = 0;

	omp_set_num_threads(2);
	#pragma omp parallel for reduction(+:s)
	for (i = 0; i < 1000000; i++) {
		s++;
	}
	printf("s = %d\n", s);

	return 0;
}
