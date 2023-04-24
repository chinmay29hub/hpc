#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000

int main() {
    int i, j, k;
    double sum;
    double *A, *B, *C;
    clock_t start, end;
    
    // Allocate memory for the matrices
    A = (double*)malloc(N*N*sizeof(double));
    B = (double*)malloc(N*N*sizeof(double));
    C = (double*)malloc(N*N*sizeof(double));
    
    // Initialize matrices A and B with random values
    for (i = 0; i < N*N; i++) {
        A[i] = rand()/(double)RAND_MAX;
        B[i] = rand()/(double)RAND_MAX;
    }
    
    // Start the timer
    start = clock();
    
    // Perform matrix multiplication C = A*B
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            sum = 0.0;
            for (k = 0; k < N; k++) {
                sum += A[i*N+k]*B[k*N+j];
            }
            C[i*N+j] = sum;
        }
    }
    
    // Stop the timer
    end = clock();
    
    // Print the execution time in seconds
    printf("Execution time: %lf seconds\n", (double)(end - start)/CLOCKS_PER_SEC);
    
    // Free memory
    free(A);
    free(B);
    free(C);
    
    return 0;
}