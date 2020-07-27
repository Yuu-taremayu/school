#include <stdio.h>

void Gauss_Jordan_Elimination(double A[3][4]);

int main(void)
{
	double A[3][4] = {{2, 3, 4, 6}, {3, 5, 2, 5}, {4, 3, 30, 32}};
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%4.f", A[i][j]);
		}
		printf("\n");
	}

	Gauss_Jordan_Elimination(A);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%4.f", A[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

void Gauss_Jordan_Elimination(double A[3][4])
{
	int N = 3;

	for (int k = 0; k < N; k++) {
		printf("k = %d\n", k);
		for (int j = k + 1; j < N + 1; j++) {
			printf("j = %d\n", j);
			A[k][j] = A[k][j] / A[k][k];
			for (int i = 0; i < N; i++) {
				printf("i = %d\n", i);
				if (i != k) {
					A[i][j] = A[i][j] - A[k][j] * A[i][k];
				}
			}
		}
	}
}
