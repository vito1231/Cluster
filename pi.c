#include <stdio.h>
#include <stdlib.h>
#include <mpi.h> /* MPI header file */
#include <time.h>
#define NUM_STEPS 100000000
int main(int argc, char *argv[]) {
 int nprocs;
 int myid;
 double start_time, end_time;
 int i;
 clock_t begin=clock();
 double x, pi;
 double sum = 0.0;
 double step = 1.0/(double) NUM_STEPS;
 /* initialize for MPI */
 MPI_Init(&argc, &argv); /* starts MPI */
 /* get number of processes */
 MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
 /* get this process's number (ranges from 0 to nprocs - 1) */
 MPI_Comm_rank(MPI_COMM_WORLD, &myid);

 /* do computation */
 for (i=myid; i < NUM_STEPS; i += nprocs) { /* changed */
 x = (i+0.5)*step;
 sum = sum + 4.0/(1.0+x*x);
 }
 sum = step * sum; /* changed */
 MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);/* added */
/* print results */
 if (myid == 0) {
 printf("parallel program results with %d processes:\n", nprocs);
 printf("pi = %g (%17.15f)\n",pi, pi);
 }
 clock_t toc=clock();
 printf("Elapsed: %f seconds: ",(double)(toc-begin)/CLOCKS_PER_SEC);

 /* clean up for MPI */
 MPI_Finalize();
 
 
 
 return 0;
}
