#include <stdio.h>
#include <omp.h>

/* Q1: How many times will you see the "Hello world!"        */
/*     message if the program is executed with "./1.hello"?  */    
/* Q2: Without changing the program, how to make it to       */
/*     print 4 times the "Hello World!" message?             */

int main ()
{
    #pragma omp parallel //num_threads(4)
    printf("Hello world!\n");
	
    return 0;
}
