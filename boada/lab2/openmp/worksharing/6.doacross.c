#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <omp.h>	/* OpenMP */

#define N 16
#define M 5

/* Q1: In which order are the "Outside" and "Inside" messages printed?     */
/* Q2: In which order are the iterations in the second loop nest executed? */
/* Q3: What would happen if you remove the invocation of sleep(1). Execute */
/*     several times to answer in the general case.                        */

int main() 
{
    float a[N], b[N], c[N];
    float a1[M][M], b1[M][M], c1[M][M];

    omp_set_num_threads(8);
    #pragma omp parallel for ordered(1) schedule(dynamic)
    for (int i=1; i<N; i++) {
        a[i] = 1.3;

        printf("Outside from %d executing %d\n", omp_get_thread_num(), i);
        #pragma omp ordered depend(sink: i-2)
	    {
	    printf("Inside from %d executing %d\n", omp_get_thread_num(), i);
	    b[i] = a[i] * b[i-1];
	    }
	#pragma omp ordered depend(source)

	c[i] = b[i] * 0.1234;
    }

    #pragma omp parallel for ordered(2) schedule(dynamic)
    for (int i=1; i<M; i++) {
        for (int j=1; j<M; j++) {
            a1[i][j] = 3.45;
            #pragma omp ordered depend(sink: i-1,j) depend(sink: i,j-1)
                {
                printf("Computing iteration %d %d\n", i, j);
                b1[i][j] = a1[i][j] * (b1[i-1][j] + b1[i][j-1]);
//                sleep(1);
                }
            #pragma omp ordered depend(source)
            c1[i][j] = b1[i][j] / 2.19;
        }
    }

    return 0;
}
