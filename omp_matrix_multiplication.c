#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

/* Main Program */

int main(int argc, char* argv[])
{
int   NoofRows_A, NoofCols_A, NoofRows_B, NoofCols_B, i,
               j, k;
float  **Matrix_A, **Matrix_B, **Result, **Checkoutput, flops;

struct timeval  TimeValue_Start;
struct timezone TimeZone_Start;

struct timeval  TimeValue_Final;
struct timezone TimeZone_Final;
long time_start, time_end, time_overhead;

printf("Read The Matrix Size Noofrows And Colums Of Matrix A and B  \n");
scanf("%d%d%d%d", &NoofRows_A, &NoofCols_A, &NoofRows_B, &NoofCols_B);

if (NoofRows_A <= 0 || NoofCols_A <= 0 || NoofRows_B <= 0 || NoofCols_B <= 0) {
printf("The NoofRows And NoofCols Should Be Of Positive Sign\n");
exit(1);
}
/* Checking For Necessary Condition */

if (NoofCols_A != NoofRows_B) {
printf("Matrix Matrix Computation Is Not Possible \n");
exit(1);
}
/* Matrix_A Elements */

Matrix_A = (float **) malloc(sizeof(float) * NoofRows_A);
for (i = 0; i < NoofRows_A; i++) {
Matrix_A[i] = (float *) malloc(sizeof(float) * NoofCols_A);
for (j = 0; j < NoofCols_A; j++)
Matrix_A[i][j] = i + j;
}

/* Matrix_B Elements */

Matrix_B = (float **) malloc(sizeof(float) * NoofRows_B);
for (i = 0; i < NoofRows_B; i++) {
Matrix_B[i] = (float *) malloc(sizeof(float) * NoofCols_B);
for (j = 0; j < NoofCols_B; j++)
Matrix_B[i][j] = i + j;
}

printf("The Matrix_A Is \n");

for (i = 0; i < NoofRows_A; i++) {
for (j = 0; j < NoofCols_A; j++)
printf("%f \t", Matrix_A[i][j]);
printf("\n");
}


printf("The Matrix_B Is \n");

for (i = 0; i < NoofRows_B; i++) {
for (j = 0; j < NoofCols_B; j++)
printf("%f \t", Matrix_B[i][j]);
printf("\n");
}


/* Dynamic Memory Allocation */

Result = (float **) malloc(sizeof(float) * NoofRows_A);
Checkoutput = (float **) malloc(sizeof(float) * NoofRows_A);

for (i = 0; i < NoofRows_A; i++) {
Result[i] = (float *) malloc(sizeof(float) * NoofCols_B);
Checkoutput[i] = (float *) malloc(sizeof(float) * NoofCols_B);
for (j = 0; j < NoofCols_B; j++) {
Result[i][j] = 0.0;
Checkoutput[i][j] = 0.0;
}
}

/*
* Checkoutput = (float **) malloc(sizeof(float) * NoofRows_A); for
* (i = 0; i < NoofRows_A; i++) { Checkoutput[i] = (float *)
* malloc(sizeof(float) * NoofCols_B); for (j = 0; j < NoofCols_B;
* j++) Checkoutput[i][j] = 0.0; }
*/
gettimeofday(&TimeValue_Start, &TimeZone_Start);

/* OpenMP Parallel For Directive */

#pragma omp parallel for private(j,k)
for (i = 0; i < NoofRows_A; i = i + 1)
for (j = 0; j < NoofCols_B; j = j + 1)
for (k = 0; k < NoofCols_A; k = k + 1)
Result[i][j] = Result[i][j] + Matrix_A[i][k] * Matrix_B[k][j];

gettimeofday(&TimeValue_Final, &TimeZone_Final);

time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
time_overhead = time_end - time_start;

printf("\nTime Overhead = %ld\n", time_overhead);

/* Serial Computation */

for (i = 0; i < NoofRows_A; i = i + 1)
for (j = 0; j < NoofCols_B; j = j + 1)
for (k = 0; k < NoofCols_A; k = k + 1)
Checkoutput[i][j] = Checkoutput[i][j] + Matrix_A[i][k] * Matrix_B[k][j];

for (i = 0; i < NoofRows_A; i = i + 1)
for (j = 0; j < NoofCols_B; j = j + 1)
if (Checkoutput[i][j] == Result[i][j])
continue;
else {
printf("There Is A Difference In Parallel Calculation \n");
exit(1);
}


printf("\nThe Matrix Computation Result Is \n");
for (i = 0; i < NoofRows_A; i = i + 1) {
for (j = 0; j < NoofCols_B; j = j + 1)
printf("%f ", Result[i][j]);
printf("\n");
}

/* Calculation Of Flops */

flops = (float) 2 *NoofCols_A * NoofCols_A * NoofCols_A / (float) time_overhead;
printf("\n\nNoofCols_A=%d\t MFlops=%fMFlops\n", NoofCols_A, flops);


/* Freeing Allocated Memory */

free(Matrix_A);
free(Matrix_B);
free(Result);
free(Checkoutput);

}