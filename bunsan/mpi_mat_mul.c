#include <stdio.h>
#include "mpi.h"

#define N (8192LL)

static void mat_set(double m[N][N], int n);
static void mat_mul(double a[N][N], double b[N][N], double c[N][N], int np);
static void mat_show(double m[N][N], int n);

int main(int argc, char **argv)
{
	double a[N][N];
	double b[N][N];
	double c[N][N];
	double rbuf_a[N][N];
	double rbuf_b[N][N];
	double rbuf_c[N][N];
	int i, j;
	int np;
	int my_rank;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	mat_set(a, N);
	mat_set(b, N);

	MPI_Scatter(a, N*N/np, MPI_DOUBLE, rbuf_a, N*N/np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(b, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	//mat_mul(a, b, c, np);
	//mat_show(a, N);

	MPI_Finalize();

	return 0;
}

static void mat_set(double m[N][N], int n)
{
	int i, j;
	double d;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				d = 1.0;
			}
			else {
				d = 0.0;
			}
			m[i][j] = d;
		}
	}
}

static void mat_mul(double a[N][N], double b[N][N], double c[N][N], int np)
{
	double rbuf_a[N][N];
	double rbuf_b[N][N];
	double rbuf_c[N][N];
	int i, j;
	int my_rank;

	MPI_Scatter(a, N*N/np, MPI_DOUBLE, rbuf_a, N*N/np, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(b, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	/*
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			rbuf_c[N][N] += a[i][j] * b[my_rank][j];
			printf("%d\n", my_rank);
		}
	}
	*/
}

static void mat_show(double m[N][N], int n)
{
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%2.2f ", m[i][j]);
		}
		printf("\n");
	}
}
