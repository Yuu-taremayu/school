#include <stdio.h>

#define ITERATION 5

int main(void)
{
	int i;
	double sum;

	sum = 123456789;
	for (i = 0; i < ITERATION; i++) {
		sum += 0.00000001;
	}
	printf("%.10lf\n", sum);

	return 0;
}
