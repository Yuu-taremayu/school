#include <stdio.h>
#include "MT.h"

#define NUM 100000

int count_point(double dataX[NUM], double dataY[NUM]);

int main(void)
{
	int i;
	int seed;
	int cnt;
	double pi;
	double dataX[NUM];
	double dataY[NUM];

	seed = 0;
	init_genrand(seed);

	for (i = 0; i < NUM; i++) {
		dataX[i] = genrand_real1();
		dataY[i] = genrand_real1();
	}

	cnt = count_point(dataX, dataY);
	pi = 4 * (double)cnt / (double)NUM;

	printf("pi = %lf\n", pi);

	return 0;
}

int count_point(double dataX[NUM], double dataY[NUM])
{
	int i;
	int cnt;

	cnt = 0;

	for (i = 0; i < NUM; i++) {
		if (dataX[i] * dataX[i] + dataY[i] * dataY[i] < 1) {
			cnt++;
		}
	}

	return cnt;
}
