/*
 * Compute pi by approximating the area under the curve f(x) = 4 / (1 + x*x)
 * between 0 and 1.
 *
 * Parallel version using OpenMP
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>        /* OpenMP */

double getusec_() {
        struct timeval time;
        gettimeofday(&time, NULL);
        return ((double)(time.tv_sec * 1000000L + time.tv_usec));
}

#define NUMITERS 10000
#define MINTASKS 2
#define MAXTASKS 64
#define STEPTASKS 2

double difference(int num_tasks, long int num_steps) {
    double x, sum;
    double step = 1.0/(double) num_steps;

    double stamp1 = getusec_();
    for (int rep=0; rep<NUMITERS ; rep++) 
        for (int iter=0; iter<num_tasks ; iter++) {
            sum = 0.0;
            for (long int i=0; i<num_steps; ++i) {
                x = (i+0.5)*step;
                sum += 4.0/(1.0+x*x);
                }
        }
    stamp1 = getusec_()-stamp1;

    double stamp2 = getusec_();
    for (int rep=0; rep<NUMITERS ; rep++) {
        for (int iter=0; iter<num_tasks ; iter++) {
            sum = 0.0;
            #pragma omp task private(x) firstprivate(sum)
            for (long int i=0; i<num_steps; ++i) {
                x = (i+0.5)*step;
                sum += 4.0/(1.0+x*x);
                }
        }
        #pragma omp taskwait
    }
    stamp2 = getusec_()-stamp2;

    return((stamp2 - stamp1)/NUMITERS);
}

int main(int argc, char *argv[]) {
    const char Usage[] = "Usage: pi <num_steps> <num_threads> \n";
    if (argc < 3) {
	fprintf(stderr, Usage);
	exit(1);
    }
    long int num_steps = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    printf("All overheads expressed in microseconds\n");
    printf("Ntasks\tOverhead per task\n");
    
    #pragma omp parallel num_threads(num_threads)
    #pragma omp single
    {
    difference(MINTASKS, num_steps);
    for (int n_tasks=MINTASKS; n_tasks<=MAXTASKS; n_tasks+=STEPTASKS) {
        double tmp = difference(n_tasks, num_steps);
    	printf("%d\t%.4f\n", n_tasks, tmp/n_tasks);
        }
    }

    return EXIT_SUCCESS;
}
