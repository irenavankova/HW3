//  File: Poisson_Jacobi.C 

#include <math.h> // to use math functions
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define l(i,j,N)  ( (i) + (j)*(N) )                     // A macro that indexes into a square N X N array
#define PI 3.14159265358979323846                       // from the Wikepedia page 

int main() {

    const int    N = 1000;       // The number of points in each direction, which does not change
    const double L = 1.;       // The length of the sides of the box
    const double h = L/(N-1);  // h = Delta x = Delta y.  There are N+1 intervals between x=0 and x=L.
    const int    T = 1000000000;      // The number of Jacobi iterations to do, should be an even number
    int T_p = 10000;   
    const double tol = 1000000;
    double *u, *unew;

    u = (double *) calloc((size_t)N+2 , sizeof(double) );
    unew = (double *) calloc((size_t)N+2 , sizeof(double) );               

    double initRnorm, newRnorm, R, sum;
    initRnorm = 0;
    int i, k; 

    //INITIALIZE
    for ( i = 0; i < N+2; i++ ) {        
        u[i] = 0;   //update u
    }
    sum = 0;
    for ( i = 1; i < N+1; i++ ) {        
        R = u[i] - 0.5*(u[i-1]+u[i+1]-h*h);        	       //update u
        sum = sum + R*R;
    }
    initRnorm = sqrt(sum);

    k = 0;		//counter

    //THE MAIN ITERATION
    while ( k < T ) {
        #pragma omp parallel
        {
            #pragma omp for
            for ( i = 1; i < N+1; i++ ) {        
                unew[i] = 0.5*(u[i-1]+u[i+1]-h*h);   //update u
            }
            #pragma omp for
            for ( i = 1; i < N+1; i++ ) {        
                u[i] = unew[i];        	       //update u
            }
        }

        k++;

        sum = 0; 
        //COMPUTE NEW RESIDUAL
        #pragma omp parallel
        {
            #pragma omp for
            for ( i = 1; i < N+1; i++ ) {        
                R = u[i] - 0.5*(u[i-1]+u[i+1]-h*h);        	       
                sum = sum + R*R;
            }
        }
        newRnorm = sqrt(sum);
        //PRINT
        if ( k%T_p == 0 ){
            printf("Iteration: %d; new res: %f; initial res: %f; ratio: %f\n",k,newRnorm,initRnorm,initRnorm/newRnorm);
        }
        if (initRnorm/newRnorm > tol){
            printf("Final iteration: %d ratio: %f\n",k,initRnorm/newRnorm);
            k = T;
        }
    }
    free(u);
    free(unew);
    return 0;
  }
         
         
         
