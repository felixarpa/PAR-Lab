#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>	/* OpenMP */
#define N 8


/* Q1: How does the sequence of printf change if the nowait clause is   */
/*     removed from the first for directive?                            */
/* Q2: If the nowait clause is removed in the second for pragma, will   */
/*     you observe any difference?                                      */

int main() 
{
    int i;

    omp_set_num_threads(8);
    #pragma omp parallel 
    {
	#pragma omp for schedule(static,2) //nowait
        for (i=0; i < N; i++) {
		int id=omp_get_thread_num();
		printf("Loop 1: (%d) gets iteration %d\n",id,i);	
        }

	#pragma omp for schedule(static, 2) nowait
        for (i=0; i < N; i++) {
		int id=omp_get_thread_num();
		printf("Loop 2: (%d) gets iteration %d\n",id,i);	
        }
    }

    return 0;
}
