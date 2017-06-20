/*
 * Compute pi by approximating the area under the curve f(x) = 4 / (1 + x*x)
 * between 0 and 1.
 *
 * Parallel version using OpenMP
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>	/* OpenMP */

double getusec_() {
        struct timeval time;
        gettimeofday(&time, NULL);
        return ((double)(time.tv_sec * 1000000L + time.tv_usec));
}

#define NUMITERS 10000

double difference (long int num_steps, int n_threads){
    double x, sum=0.0;
    double step = 1.0/(double) num_steps;

    double stamp1=getusec_();
    for (int iter=0; iter<NUMITERS ; iter++) {
        sum = 0.0;
        for (long int i=0; i<num_steps; ++i) {
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
            }
        }
    stamp1=getusec_()-stamp1;

    omp_set_num_threads(n_threads);
    double stamp2=getusec_();
    for (int iter=0; iter<NUMITERS ; iter++) {
        sum = 0.0;
        #pragma omp parallel private(x) firstprivate(sum)
        for (long int i=0; i<num_steps; ++i) {
            x = (i+0.5)*step;
            sum += 4.0/(1.0+x*x);
            }
        }
    stamp2=getusec_()-stamp2;
    return((stamp2-stamp1)/NUMITERS);
}

int main(int argc, char *argv[]) {
    const char Usage[] = "Usage: pi <num_steps> <max_threads>\n";
    if (argc < 3) {
	fprintf(stderr, Usage);
	exit(1);
    }
    long int num_steps = atoi(argv[1]);
    int max_threads = atoi(argv[2]);

    printf("All overheads expressed in microseconds\n");
    printf("Nthr\tOverhead\tOverhead per thread\n");
    
    for (int n_threads=2; n_threads<=max_threads; n_threads++) {
        double tmp = difference(num_steps, n_threads);
    	printf("%d\t%.4f\t\t%.4f\n", n_threads, tmp, tmp/n_threads);
        }

    return EXIT_SUCCESS;
}
