#include <stdio.h>
#include "mpi.h"

#define N (32LL)

static void mat_set(double m[N][N], int n);
static void mat_mul(double a[N][N], double b[N][N], double c[N][N], int my_rank, int np);
static void mat_show(double m[N][N], int n);

int main(int argc, char **argv)
{
	double a[N][N];
	double b[N][N];
	double c[N][N];
	int i, j;
	int np;
	int my_rank;
	double ts;
	double te;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if (my_rank == 0) {
		mat_set(a, N);
		mat_set(b, N);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	ts = MPI_Wtime();
	mat_mul(a, b, c, my_rank, np);
	MPI_Barrier(MPI_COMM_WORLD);
	te = MPI_Wtime();

	if (my_rank == 0) {
		printf("np = %d, N = %d, time = %lf\n", np, N, te - ts);
	}

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
				m[i][j] = 1;
			}
			else {
				m[i][j] = 0;
			}
		}
	}
}

static void mat_mul(double a[N][N], double b[N][N], double c[N][N], int my_rank, int np)
{
	double rbuf_b[N][N];
	double rbuf_c[N][N];
	int i, j, k;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			c[i][j] = 0;
			rbuf_b[i][j] = 0;
			rbuf_c[i][j] = 0;
		}
	}
	
	MPI_Bcast(a, N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Scatter(b, N*N/np, MPI_DOUBLE, rbuf_b, N*N/np, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			for (k = 0; k < N/np; k++) {
				rbuf_c[i][j] += a[i][k] * rbuf_b[k][j];
			}
		}
	}
	MPI_Allgather(rbuf_c, N*N/np, MPI_DOUBLE, c, N*N/np, MPI_DOUBLE, MPI_COMM_WORLD);
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
	printf("\n");
}
