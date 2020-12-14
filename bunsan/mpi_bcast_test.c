#include  <stdio.h>
#include  "mpi.h"

int
main(int argc,char **argv)
{
  int   my_rank;
  int   np;
  int   i;
  int   sum;
  int   d[10];
  MPI_Status  status;

  /* 初期化 */
  MPI_Init(&argc,&argv);

  /* my_rank: 自分のプロセス番号 */
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

  /* np: プロセス数 */
  MPI_Comm_size(MPI_COMM_WORLD,&np);

  if (my_rank == np - 1){
    for (i = 0;i < 10;i++) d[i] = i;
  }
  MPI_Bcast(d,10,MPI_INT,np - 1,MPI_COMM_WORLD);
  sum = 0;
  for (i = 0;i < 10;i++){
    sum += d[i];
  }
  printf("rank %d:sum=%d\n",my_rank,sum);
  MPI_Finalize();
}
