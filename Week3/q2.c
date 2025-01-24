#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, N, M, i;
    int *A = NULL, B[10];
    float avg = 0.0, *D = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter value of M: ");
        scanf("%d", &M);
        N = size;
        A = (int *)malloc(M * N * sizeof(int));
        printf("Enter %d values for A: ", M * N);
        for (i = 0; i < M * N; i++) scanf("%d", &A[i]);
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(A, M, MPI_INT, B, M, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < M; i++) avg += (float)B[i] / M;

    // Allocate the gather buffer on all processes before gathering
    D = (float *)malloc(size * sizeof(float));

    MPI_Gather(&avg, 1, MPI_FLOAT, D, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        avg = 0.0;
        for (i = 0; i < N; i++) avg += D[i] / N;
        printf("\nFinal Average = %f\n", avg);
        free(A);
        free(D);
    }

    MPI_Finalize();
    return 0;
}
