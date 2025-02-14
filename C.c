#include <mpi.h> 
#include <stdio.h> 
 int main(int argc, char *argv[]) {
    int rank, size;
    char str[100],b[100]; 
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status;

    if (rank == 0 ) {
        printf("Enter the string: \n");
        scanf("%s", str);
    }

    MPI_Scatter(&str,1,MPI_CHAR,&b,1,MPI_CHAR,0,MPI_COMM_WORLD);
    if (b[0] >= 97) {
        b[0] = b[0] - 32; 
    }
    else {
        b[0] = b[0] + 32;     
    }
    MPI_Gather(&b,1,MPI_CHAR,&str,1,MPI_CHAR,0,MPI_COMM_WORLD);
    printf("The string is %s\n",str);
    
    MPI_Finalize();

    return 0;

    }