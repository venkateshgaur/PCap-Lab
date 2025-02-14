// A section Question , a string input string distribute the character, to each process, and if the process is odd rank check if character is vowel, else if check if it's consonant.


#include<mpi.h> 
#include <mpi.h> 
#include <stdio.h> 
 int main(int argc, char *argv[]) {
    int rank, size;
    char a[100],b[100]; 
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Status status; 
    
    if (rank == 0 ) {
        printf("Enter the string: \n"); 
        scanf("%s",a);

    }

    MPI_Scatter(&a,1,MPI_CHAR,&b,1,MPI_CHAR,0,MPI_COMM_WORLD);
    
    if (rank % 2 != 0 ) {
        if  (b[0] == 'a' || b[0] == 'A' ||
        b[0] == 'e' || b[0] == 'E' ||
        b[0] == 'i' || b[0] == 'I' ||
        b[0] == 'o' || b[0] == 'O' ||
        b[0] == 'u' || b[0] == 'U')  
            printf("The character is a vowel \n");

    }
    if (rank % 2 == 0 ) {
        if  (!(b[0] == 'a' || b[0] == 'A' ||
        b[0] == 'e' || b[0] == 'E' ||
        b[0] == 'i' || b[0] == 'I' ||
        b[0] == 'o' || b[0] == 'O' ||
        b[0] == 'u' || b[0] == 'U'))
            printf("The character is a consonant \n");

    }
    
    
    MPI_Finalize();
    return 0; 
 } 


 
    
 
