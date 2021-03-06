/******************************************************************************
* FILE: omp_bug2.c
* DESCRIPTION:
*   Another OpenMP program with a bug. 
* AUTHOR: Blaise Barney 
* LAST REVISED: 04/06/05 
******************************************************************************/

/******************************************************************************
* Irena's comments
* Bug: Every run the total is different, yet it is the same on each processor. Making i and tid and total private to each processor seems to fix the problem, so that sum of totals is the same.
* Also return 0 is added at the end of main to remove this message: make: *** [bug3] Error #
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) 
{
int nthreads, i, tid;
float total;

/*** Spawn parallel region ***/
#pragma omp parallel private(tid,total,i) 
  {
  /* Obtain thread number */
  tid = omp_get_thread_num();
  /* Only master thread does this */
  if (tid == 0) {
    nthreads = omp_get_num_threads();
    printf("Number of threads = %d\n", nthreads);
    }
  printf("Thread %d is starting...\n",tid);

  #pragma omp barrier

  /* do some work */
  total = 0.0;
  #pragma omp for schedule(dynamic,10)
  for (i=0; i<1000000; i++){
     total = total + i*1.0;
  }
  #pragma omp barrier
  printf ("Thread %d is done! Total= %e\n",tid,total);

  #pragma omp barrier
  
  } /*** End of parallel region ***/
  return 0;
}
