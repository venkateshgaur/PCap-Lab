#include "mpi.h"
#include <stdio.h>

int main(int argc,char *argv[])
{
    int rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank%2==0){
        int prod=1;
        for(int i=2;i<=rank;i++){
            prod*=i;
        }
        printf("Factorial is %d for rank number %d\n",prod,rank);
    }
    else{
            int a = 0, b = 1, next;
    for (int i = 1; i <= rank; i++) {
        next = a + b;        
        a = b;               
        b = next;            
    }
    printf("Fibonacci number at rank number %d is %d\n",rank,b);
    }
    MPI_Finalize();

    return 0;
}