#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <tareador.h>

#define size 16
double A[size]; // vector A globally declared
double * B;  // vector B dynamically allocated in main program

double my_func (double Ai, double Bi){
double comp;

   comp = Ai * Bi;
   int i;
   for (i=0; i < 500; i++)
        comp += i;

   return (comp);
}

void dot_product (long N, double A[N], double B[N], double *acc){
	double prod;
        int i;

	*acc=0.0;
 	for (i=0; i<N; i++) {
		tareador_start_task("dot_product_it");
		prod = my_func(A[i], B[i]);
		tareador_disable_object(acc);
		*acc += prod;
		tareador_enable_object(acc);
		tareador_end_task("dot_product_it");
	}
}

int main(int argc, char **argv) {
    struct timeval start;
    struct timeval stop;
    unsigned long elapsed;
    double result;

    double *B = malloc(size*sizeof(double));

    tareador_ON ();

    int i;

    tareador_start_task("init_A");
    for (i=0; i< size; i++) A[i]=i;
    tareador_end_task("init_A");

    tareador_start_task("init_B");
    for (i=0; i< size; i++) B[i]=2*i;
    tareador_end_task("init_B");

    gettimeofday(&start,NULL);

    tareador_start_task("dot_product");
    dot_product (size, A, B, &result);
    tareador_end_task("dot_product");

    tareador_OFF ();

    gettimeofday(&stop,NULL);
    elapsed = 1000000 * (stop.tv_sec - start.tv_sec);
    elapsed += stop.tv_usec - start.tv_usec;
    printf("Result of Dot product i= %le\n", result);
    printf("Execution time (us): %lu \n", elapsed);

    return 0;
}
