#include <stdio.h>
#include "mpi.h"

#define SIZE 8

int main(int argc, char **argv)
{
	int my_rank;
	int np;
	int i;
	int sbuf_a[SIZE];
	int sbuf_b[SIZE];
	int rbuf_a[SIZE];
	int rbuf_b[SIZE];
	int sum;
	int r;
	MPI_Status status;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if (my_rank == 0) {
		for (i = 0; i < SIZE; i++) {
			sbuf_a[i] = i;
			sbuf_b[i] = i;
		}
	}

	MPI_Scatter(sbuf_a, SIZE/np, MPI_INT, rbuf_a, SIZE/np, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(sbuf_b, SIZE/np, MPI_INT, rbuf_b, SIZE/np, MPI_INT, 0, MPI_COMM_WORLD);
	for (i = 0; i < SIZE/np; i++) {
		sum += rbuf_a[i] * rbuf_b[i];
	}
	printf("rank %d:sum=%d\n", my_rank, sum);

	MPI_Reduce(&sum, &r, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (my_rank == 0) {
		printf("inner product=%d\n", r);
	}

	MPI_Finalize();
	return 0;
}
