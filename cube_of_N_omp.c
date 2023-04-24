#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char** argv) {
    int start = 1; // start of range
    int end = 20; // end of range
    int n = end - start + 1; // number of elements
    int cubes[n]; // array to hold cube of each element

    #pragma omp parallel for
    for (int i = start; i <= end; i++) {
        cubes[i-start] = i*i*i;
    }

    // print the cubes
    for (int i = start; i <= end; i++) {
        printf("%d^3 = %d\n", i, cubes[i-start]);
    }

    return 0;
}