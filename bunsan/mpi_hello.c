#include	<stdio.h>
#include	<string.h>
#include	<unistd.h>
#include	"mpi.h"

int
main(int argc,char **argv)
{
  int	my_rank, np, source, dest, tag;
  char	message[100];
  MPI_Status	status;
  
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
  MPI_Comm_size(MPI_COMM_WORLD,&np);
  
  tag = 0;
  dest = 0;
  if (my_rank != 0){
    sprintf(message,"Hello. My rank is %d",my_rank);
    MPI_Send(message,strlen(message) + 1,MPI_CHAR,dest,tag,MPI_COMM_WORLD);
  }else{
    for (source = 1;source < np;source++){
      MPI_Recv(message,100,MPI_CHAR,source,tag,MPI_COMM_WORLD,&status);
      printf("%s\n",message);
    }
  }
  MPI_Finalize();
}
