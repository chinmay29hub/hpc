#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    double radius = 5.0;
    double area = 0.0;
   double pi = 3.14159;
    int num_threads = 4;
#pragma omp parallel num_threads(num_threads)
    {
       // int tid = omp_get_thread_num();
        double local_area = 0.0;
 #pragma omp for
        for (int i = 0; i < 10000000; i++) {
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;
            if (x*x + y*y <= radius*radius) {
                local_area += 1.0;
            }
        }
#pragma omp critical
        {
            area += local_area;
        }
    }
  area = 4.0 *pi* radius * radius * (area / 10000000.0) / num_threads;
    printf("Area of circle with radius %f is %f\n", radius, area);
return 0;
}
