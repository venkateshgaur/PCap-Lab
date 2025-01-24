#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_STRING_LENGTH 1000

int main(int argc, char *argv[]) {
    int rank, size, length_per_process, remainder;
    char S1[MAX_STRING_LENGTH], S2[MAX_STRING_LENGTH], result[MAX_STRING_LENGTH];
    char *local_S1, *local_S2, *local_result;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter string 1: ");
        fgets(S1, MAX_STRING_LENGTH, stdin);
        printf("Enter string 2: ");
        fgets(S2, MAX_STRING_LENGTH, stdin);
        S1[strcspn(S1, "\n")] = '\0'; // Remove newline
        S2[strcspn(S2, "\n")] = '\0'; // Remove newline
        if (strlen(S1) != strlen(S2)) {
            printf("Strings must have the same length.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    MPI_Bcast(S1, MAX_STRING_LENGTH, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(S2, MAX_STRING_LENGTH, MPI_CHAR, 0, MPI_COMM_WORLD);

    int length = strlen(S1);
    length_per_process = length / size;
    remainder = length % size;

    local_S1 = malloc(length_per_process + (rank < remainder));
    local_S2 = malloc(length_per_process + (rank < remainder));
    local_result = malloc(length_per_process + (rank < remainder));

    MPI_Scatter(S1, length_per_process, MPI_CHAR, local_S1, length_per_process + (rank < remainder), MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(S2, length_per_process, MPI_CHAR, local_S2, length_per_process + (rank < remainder), MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = 0; i < length_per_process + (rank < remainder); i++)
        local_result[i] = (local_S1[i] == local_S2[i]) ? local_S1[i] : 'X';

    MPI_Gather(local_result, length_per_process + (rank < remainder), MPI_CHAR, result, length_per_process + (rank < remainder), MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        result[length] = '\0';  // Null-terminate
        printf("Resultant string: %s\n", result);
    }

    free(local_S1);
    free(local_S2);
    free(local_result);

    MPI_Finalize();
    return 0;
}


    
