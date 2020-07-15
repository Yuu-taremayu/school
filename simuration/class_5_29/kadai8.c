#include <stdio.h>
#include <math.h>

int main(void)
{
	double a[3];
	for (int i = 0; i < 3; i++) {
		printf("plz input num [%d]:", i);
		scanf("%lf", &a[i]);
	}

	/* calculation D */
	double D;
	int comp_flag = 0;

	D = pow(a[1], 2) - (4 * a[0] * a[2]);
	/*judge D*/
	if (D < 0) {
		D *= -1;
		comp_flag = 1;
	}

	/* real solution */
	if (comp_flag == 0) {
		double x1 = 0, x2 = 0;

		x1 = (-a[1] + sqrt(D)) / (2 * a[0]);
		x2 = a[0] / (a[2] * x1);

		printf("x1 = %lf\nx2 = %lf\n", x1, x2);
	}
	/* imaginary solution */
	else {
		double x1_re = 0, x1_im = 0;

		x1_re = -a[1] / (2 * a[0]);
		x1_im = sqrt(D) / (2 * a[0]);
		
		printf("x1 = %lf + %lfi\nx2 = %lf - %lfi\n", x1_re, x1_im, x1_re, x1_im);
	}
	return 0;
}
