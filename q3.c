#include "mpi.h"
#include <stdio.h>

int main (int argc, char*argv[]){
	int rank;
	int a = 60;
	int b = 5;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if (rank == 0) {
		printf("%d + %d = %d for rank number %d \n",a,b,a+b,rank);
	}
	else if (rank == 1) {
		printf("%d - %d = %d for rank number %d \n",a,b,a-b,rank);
	}
	else if (rank == 2) {
		printf("%d* %d = %d for rank number %d \n",a,b,a*b,rank);
	}
	else if (rank == 3) {
		printf("%d / %d = %d for rank number %d \n",a,b,a/b,rank);
	}

	
	MPI_Finalize();
	return 0;
}
 