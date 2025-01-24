#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size, n, i, local_count = 0;
    char *A = NULL, B[10];
    int *D = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Allocate memory for the string based on the size and maximum length of 10 characters
        A = (char *)malloc(sizeof(char) * size * 10);
        printf("Enter string divisible by %d: ", size);
        scanf("%s", A);
        
        // Ensure the string length is divisible by the number of processes
        n = strlen(A) / size;
    }

    // Broadcast the length per process to all processes
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter the string across all processes
    MPI_Scatter(A, n, MPI_CHAR, B, n, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Each process counts the non-vowels (consonants)
    for (i = 0; i < n; i++) {
        if (!strchr("aeiouAEIOU", B[i])) {
            local_count++;
        }
    }

    // Gather the local counts from all processes
    D = (int *)malloc(size * sizeof(int));
    MPI_Gather(&local_count, 1, MPI_INT, D, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Rank 0 will sum the counts and print the results
    if (rank == 0) {
        int total_count = 0;
        for (i = 0; i < size; i++) {
            total_count += D[i];
            printf("Process %d found %d non-vowels\n", i, D[i]);
        }
        printf("\nFinal count of Non-Vowels: %d\n", total_count);
        free(A);  // Free the memory allocated for string A
    }

    // Free dynamically allocated memory for the counts array
    free(D);

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
