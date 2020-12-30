#include <stdio.h>

#define STEPNUM 1000

double func(double x);
double lagrange(double x, double dataX[], double dataY[], int data_num);
double base(int i, double x, double dataX[], int data_num);

int main(void)
{
	double dataX1[5];
	double dataY1[5];
	double dataX2[11];
	double dataY2[11];
	double dataX3[21];
	double dataY3[21];
	double xa, xb;
	double step;
	int i;
	FILE *fp, *fp1, *fp2, *fp3;

	xa = -1;
	xb = 1;

	step = (xb-xa) / (5-1);
	for (i = 0; i < 5; i++) {
		dataX1[i] = xa + step*i;
		dataY1[i] = func(dataX1[i]);
	}

	step = (xb-xa) / (11-1);
	for (i = 0; i < 11; i++) {
		dataX2[i] = xa + step*i;
		dataY2[i] = func(dataX2[i]);
	}
	
	step = (xb-xa) / (21-1);
	for (i = 0; i < 21; i++) {
		dataX3[i] = xa + step*i;
		dataY3[i] = func(dataX3[i]);
	}

	step = (xb-xa) / STEPNUM;
	double x[STEPNUM];
	double y[STEPNUM];
	double L1[STEPNUM];
	double L2[STEPNUM];
	double L3[STEPNUM];

	for (i = 0; i < STEPNUM; i++) {
		x[i] = 0;
		y[i] = 0;
		L1[i] = 0;
		L2[i] = 0;
		L3[i] = 0;
	}

	for (i = 0; i < STEPNUM; i++) {
		x[i] = xa + step*(double)i;
		y[i] = func(x[i]);
		L1[i] = lagrange(x[i], dataX1, dataY1, 5);
		L2[i] = lagrange(x[i], dataX2, dataY2, 11);
		L3[i] = lagrange(x[i], dataX3, dataY3, 21);
	}

	fp = fopen("lagrange2.dat", "w");
	fp1 = fopen("lagrange2_1.dat", "w");
	fp2 = fopen("lagrange2_2.dat", "w");
	fp3 = fopen("lagrange2_3.dat", "w");
	if (fp == NULL || fp1 == NULL || fp2 == NULL || fp3 == NULL) {
		printf("ERROR\n");
		return -1;
	}

	for (i = 0; i < STEPNUM; i++) {
		fprintf(fp, "%lf %lf\n", x[i], y[i]);
		fprintf(fp1, "%lf %lf\n", x[i], L1[i]);
		fprintf(fp2, "%lf %lf\n", x[i], L2[i]);
		fprintf(fp3, "%lf %lf\n", x[i], L3[i]);
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}

double func(double x)
{
	return 1 / (1 + 25*x*x);
}

double lagrange(double x, double dataX[], double dataY[], int data_num)
{
	double l;
	double L;
	int i;

	l = 0;
	L = 0;
	for (i = 0; i < data_num; i++) {
		l = base(i, x, dataX, data_num) / base(i, dataX[i], dataX, data_num);
		L += dataY[i] * l;
	}

	return L;
}

double base(int i, double x, double dataX[], int data_num)
{
	double l;
	int k;

	l = 1;
	for (k = 0; k < data_num; k++) {
		if (i != k) {
			l *= x - dataX[k];
		}
	}

	return l;
}
