#include <stdio.h>

double lagrange(double x, double dataX[3], double dataY[3]);
double base(int i, double x, double dataX[3]);

int main(void)
{
	double dataX[3] = {1.0, 3.0, 4.0};
	double dataY[3] = {1.0, 2.0, 5.0};
	int data_num;
	double xa, xb;
	double step;
	int i;
	FILE *fp;

	xa = -1;
	xb = 5;
	step = 0.01;
	data_num = (int)((xb-xa) / step);

	double x[data_num];
	double y[data_num];

	for (i = 0; i < data_num; i++) {
		x[i] = 0;
		y[i] = 0;
	}


	for (i = 0; i < data_num; i++) {
		x[i] = xa + step*i;
		y[i] = lagrange(x[i], dataX, dataY);
	}

	fp = fopen("lagrange1.dat", "w");
	if (fp == NULL) {
		printf("ERROR\n");
		return -1;
	}

	for (i = 0; i < data_num; i++) {
		fprintf(fp, "%lf %lf\n", x[i], y[i]);
	}
	fclose(fp);

	return 0;
}

double lagrange(double x, double dataX[3], double dataY[3])
{
	double l;
	double L;
	int i;

	l = 0;
	L = 0;
	for (i = 0; i < 3; i++) {
		l = base(i, x, dataX) / base(i, dataX[i], dataX);
		L += dataY[i] * l;
	}

	return L;
}

double base(int i, double x, double dataX[3])
{
	double l;
	int k;

	l = 1;
	for (k = 0; k < 3; k++) {
		if (i != k) {
			l *= x - dataX[k];
		}
	}

	return l;
}
