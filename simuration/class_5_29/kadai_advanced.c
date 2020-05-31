#include <stdio.h>
#include <math.h>

int main(void)
{
	float sum = 1;
	float exp = 1;
	float fac = 1;

	/* input num of exponential */
	float index;
	printf("plz input e^?:");
	scanf("%f", &index);
	exp = index;

	/* input num of times to approximate */
	int times;
	printf("plz input times:");
	scanf("%d", &times);

	/* calculation Taylor series */
	for (int i = 1; i <= times; i++) {
		sum += exp / fac;
		exp *= index;
		fac *= i + 1;
	}

	printf("sum = %16.16lf\n", sum);

	return 0;
}
