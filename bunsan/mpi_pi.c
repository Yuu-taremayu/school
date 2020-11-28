#include	<stdio.h>
#include	<stdlib.h>
#include	<mpi.h>
#include	<math.h>

#define	F(x)	(4.0L / (1.0L + x * x))

double pi(int n_intervals, int np, int my_rank);

int main(int argc, char **argv)
{
  int n_intervals;
  int np;
  int my_rank;
  int i;
  double s, s_total;
  MPI_Status status;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  
  n_intervals = 10000000;

  if (my_rank != 0) {
	  s = pi(n_intervals, np, my_rank);
	  MPI_Send(&s, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
  }
  else {
	  s_total = pi(n_intervals, np, my_rank);
	  for (i = 1; i < np; i++) {
		  MPI_Recv(&s, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
		  s_total += s;
	  }
	  printf("pi = %.30lf\n",s_total / n_intervals);
  }
  MPI_Finalize();
}

double pi(int n_intervals, int np, int my_rank)
{
  int i, start, end;
  double sum,step,x;
  
  start = my_rank * (n_intervals / np);
  end = (my_rank + 1) * (n_intervals / np);
  step = 1.0L / n_intervals;
  sum = 0.0L;
  for (i = start;i < end;i++){
    x = (i + 0.5L) * step;
    sum += F(x);
  }
  return sum;
}
