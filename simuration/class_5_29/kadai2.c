#include <stdio.h>

int main(void)
{
	double x = 0.0;

	for (int i = 0; i < 1000000; i++) {
		x += 0.1;
		printf("x = %16.16lf\n", x);
	}
	printf("Done!\n");
	return 0;
}
