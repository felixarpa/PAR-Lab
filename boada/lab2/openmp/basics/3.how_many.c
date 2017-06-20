#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/* If the OMP_NUM_THREADS variable is set to 8 with                     */
/* export OMP_NUM_THREADS=8                                             */
/* Q1: How many "Hello world ..." lines are printed on the screen?      */
/* Q2: If the if(0)}clause is commented in the last parallel directive, */
/*     how many "Hello world ..." lines are printed on the screen?      */

int main ()
{
    #pragma omp parallel
    printf("Hello world from the first parallel!\n");
	
    omp_set_num_threads(2);
    #pragma omp parallel
    printf("Hello world from the second parallel!\n");

    #pragma omp parallel num_threads(3)
    printf("Hello world from the third parallel!\n");

    #pragma omp parallel
    printf("Hello world from the fourth  parallel!\n");

    srand(time(0));
    #pragma omp parallel num_threads(rand()%4+1) if(0) 
    printf("Hello world from the fifth parallel!\n");

    return 0;
}
