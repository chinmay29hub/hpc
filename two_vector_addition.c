#include <stdio.h>
#include <cuda_runtime.h>

__global__ void vectorAdd(int *a, int *b, int *c, int n) {
    int i = threadIdx.x;
    if (i < n) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    const int n = 1000000;
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;

    a = (int*)malloc(n * sizeof(int));
    b = (int*)malloc(n * sizeof(int));
    c = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
    }

    cudaMalloc((void**)&d_a, n * sizeof(int));
    cudaMalloc((void**)&d_b, n * sizeof(int));
    cudaMalloc((void**)&d_c, n * sizeof(int));

    cudaMemcpy(d_a, a, n * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, n * sizeof(int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (n + blockSize - 1) / blockSize;

    vectorAdd<<<numBlocks, blockSize>>>(d_a, d_b, d_c, n);

    cudaMemcpy(c, d_c, n * sizeof(int), cudaMemcpyDeviceToHost);

    for (int i = 0; i < n; i++) {
        printf("%d ", c[i]);
    }
    printf("\n");

    free(a);
    free(b);
    free(c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}