#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>	/* OpenMP */
#define N 16


/* Q1: How can you avoid the intermixing of printf messages in the two     */
/*     loops?                                                              */
/* Q2: How can you ensure that a thread always executes two consecutive    */
/*     in order during the execution of the first loop?                    */

int main() 
{
    int i;

    omp_set_num_threads(8);
    #pragma omp parallel 
    {
	#pragma omp for schedule(dynamic, 2) ordered//nowait
        for (i=0; i < N; i++) {
		int id=omp_get_thread_num();
		printf("Loop 1 - (%d) gets iteration %d\n",id,i);
        }

        #pragma omp for schedule(dynamic) ordered
        for (i=0; i < N; i++) {
		int id=omp_get_thread_num();
		#pragma omp ordered
		printf("Loop 2 - (%d) gets iteration %d\n",id,i);	
        }
    }

    return 0;
}
