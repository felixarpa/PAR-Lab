#include <stdio.h>
#include <omp.h>

/* If the OMP_NUM_THREADS variable is set to 8 with     */
/* export OMP_NUM_THREADS=8                             */
/* Q1: Is the execution of the program correct? Add a   */
/*     data sharing clause to make it correct           */
/* Q2: Are the lines always printed in the same order?  */
/*     Could the messages appear intermixed? 	        */ 

int main ()
{
    int id;
    #pragma omp parallel private(id)
    {
	id =omp_get_thread_num();
	printf("(%d) Hello ",id);
	printf("(%d) world!\n",id);
    }
    return 0;
}
