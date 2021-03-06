/******************************************************************************
* FILE: omp_bug6.c
* DESCRIPTION:
*   This program compiles and runs fine, but produces the wrong result.
*   Compare to omp_orphan.c.
* AUTHOR: Blaise Barney  6/05
* LAST REVISED: 06/30/05
******************************************************************************/

/******************************************************************************
* Irena's comments
* Bug: the code does not even compile withoout errors. The problem is in the defined scope of sum.
* Need to define it globally outside the functions, then it compiles.
* Also return 0 is added at the end of main to remove this message: make: *** [bug3] Error 8
******************************************************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define VECLEN 100

float a[VECLEN], b[VECLEN];
float sum;

float dotprod ()
{
int i,tid;
//float sum;

tid = omp_get_thread_num();
#pragma omp for reduction(+:sum)
  for (i=0; i < VECLEN; i++)
    {
    sum = sum + (a[i]*b[i]);
    printf("  tid= %d i=%d\n",tid,i);
    }
}


int main (int argc, char *argv[]) {
int i;
float sum;

for (i=0; i < VECLEN; i++)
  a[i] = b[i] = 1.0 * i;
sum = 0.0;

#pragma omp parallel shared(sum)
  dotprod(sum);

printf("Sum = %f\n",sum);
return 0;

}

