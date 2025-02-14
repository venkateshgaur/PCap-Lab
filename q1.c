//For D section today they had to do something like
//Input array of strings at process 0 and distribute to processes
//At each process do String reversal + toggle
//Then String concatenation one by one through point to point communication from process 1, 2 ... cycling back to 0
//Display final result at process 0
//String
//Matrix
/*
 if rank == 0 { 
 } MPI Scan/Scatter/Broadcast/Gather/Reduce


*/
#include<stdio.h> // loads the library to execute printf,scanf
#include<mpi.h>
#include<string.h> 


int main(int argc, char *argv[]) {
    int rank,size; 
    char a[100][100];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status; 
    if (rank == 0) {
 // array of strings and strings arrays of characters therefore 2D array 
        printf("Enter the strings: \n");
        for(int i = 0; i < size; i++) 
            scanf("%s", a[i]);

    }    
    MPI_Scatter(a,100,MPI_CHAR,a,100,MPI_CHAR,0,MPI_COMM_WORLD);
    printf("Rank:%d and String:%s\n",rank,a[0]);

    if (rank == 0) {
        MPI_Send(a[0],100,MPI_CHAR,1,1,MPI_COMM_WORLD); 
        MPI_Recv(a[1],100,MPI_CHAR,3,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
        printf("%d | %s\n", rank, a[1]);
    }
    else {
        MPI_Recv(a[1],100,MPI_CHAR,rank-1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE); 
        strcat(a[0], a[1]);
        MPI_Send(a[0],100,MPI_CHAR,(rank + 1) % size,1,MPI_COMM_WORLD);  
    } 

    MPI_Finalize();
}

    

    // when something is capital it means it's a constant
