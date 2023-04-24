# hpc


```
sudo apt install mpich

mpicc hello_world_mpi.c -o hello_world_mpi

mpirun -np 5 ./hello_world_mpi
```


```
export OMP_NUM_THREADS=4

gcc -fopenmp area_circle_openmp.c -o area_circle_openmp.out

./area_circle_openmp.out
```
