#include <stdio.h>
#include <omp.h>
#define N 20
#define NUM_THREADS 4

/* Q1: How many messages the program prints? Which iterations      */
/*     of the loop is each thread executing?                       */
/* Q2: Change the directive to ensure that each thread executes    */
/*     the appropriate iterations.                                 */

int main() 
{
    int i;

    #pragma omp parallel num_threads(NUM_THREADS) private(i) 
    {
//	int i;
	int id=omp_get_thread_num();
        for (i=id; i < N; i=i+NUM_THREADS) {
		printf("Thread ID %d Iter %d\n",id,i);	
        }
    }
    return 0;
}
