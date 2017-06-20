#include <stdio.h>
#include <omp.h>

/* Q1: Which is the value of x after the execution of each     */
/*     parallel region with different data-sharing attribute   */
/*     (shared, private and firstprivate)?                     */
/* Q2: Change the first directive to ensure that the value     */
/*     after the first parallel is always 8.                   */

int main ()
{
    omp_set_num_threads(8);

    int x=0;
    #pragma omp parallel shared(x) 
    {
	x++;
	#pragma omp barrier
//	if (omp_get_thread_num() == 0) printf("After first parallel (shared) x is: %d\n",x);
    }
    printf("After first parallel (shared) x is: %d\n", x);

    x=0;
    #pragma omp parallel private(x)
    {
	x++;
    }
    printf("After second parallel (private) x is: %d\n",x);

    x=0;
    #pragma omp parallel firstprivate(x)
    {
	x++;
    }
    printf("After third  parallel (first private) x is: %d\n",x);
  
    return 0;
}
