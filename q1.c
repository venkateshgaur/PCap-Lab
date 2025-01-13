#include "mpi.h"
#include <stdio.h>
#include <math.h>

int main (int argc, char*argv[])
{
	int rank;
	int x =5; 

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int ans = pow(x,rank);
	printf("%d %d \n",ans,rank);
	MPI_Finalize();
	return 0;
}
