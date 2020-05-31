#include <stdio.h>

int main(void)
{
	double x = 123456789.0;

	for (int i = 0; i < 10; i++) {
		x += 0.000000001;
		printf("x = %16.16lf\n", x);
	}

	printf("Done!\n");
	return 0;
}
