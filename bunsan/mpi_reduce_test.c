#include  <stdio.h>
#include  "mpi.h"

#define SIZE	(80)
int
main(int argc,char **argv)
{
  int   my_rank;
  int   np;
  int   i;
  int   sum;
  int   sbuf[SIZE];
  int   rbuf[SIZE];
  MPI_Status  status;

  /* 初期化 */
  MPI_Init(&argc,&argv);

  /* my_rank: 自分のプロセス番号 */
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

  /* np: プロセス数 */
  MPI_Comm_size(MPI_COMM_WORLD,&np);
  for (i = 0;i < SIZE;i++){
    sbuf[i] = i;
  }
  MPI_Reduce(sbuf, rbuf, SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (my_rank == 0){
    for (i = 0;i < SIZE;i++){
      if (i % 20 == 0) printf("\n");
      printf("%4d",rbuf[i]);
    }
    printf("\n");
  }
  
  MPI_Finalize();
}
