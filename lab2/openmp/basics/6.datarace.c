#include <stdio.h>
#include <omp.h>
#define N 1 << 10
#define NUM_THREADS 8

/* Execute several times before answering the questions   */
/* Q1: Is the program always executing correctly? Add two */
/*     alternative directives to make it correct.         */

int main() 
{
    int i, x=0;

    omp_set_num_threads(NUM_THREADS);
    
    #pragma omp parallel private(i)
    #pragma omp single
    #pragma omp task
    {
	int id=omp_get_thread_num();
        for (i=id; i < N; i+=NUM_THREADS) {
		x++;
        }
    }
    #pragma omp taskwait
    if (x==N) printf("Congratulations!, program executed correctly (x = %d)\n", x);
    else printf("Sorry, something went wrong, value of x = %d\n", x);

    return 0;
}
