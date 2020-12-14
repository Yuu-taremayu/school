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
  if (my_rank == 0 && SIZE % np != 0){
    printf(
      "正しく計算できません．%d % プロセス数 = 0 になる数をしてください\n",SIZE
    );
  }
  for (i = 0;i < SIZE / np;i++){
    sbuf[i] = (SIZE / np) * my_rank + i;
  }
  MPI_Gather(sbuf,SIZE/np,MPI_INT,rbuf,SIZE/np,MPI_INT,0,MPI_COMM_WORLD);
  sum = 0;
  if (my_rank == 0){
    for (i = 0;i < SIZE;i++){
      if (i % 20 == 0) printf("\n");
      sum += rbuf[i];
      printf("%3d",rbuf[i]);
    }
    printf("\nrank %d:sum=%d\n",my_rank,sum);
  }
  MPI_Finalize();
}
