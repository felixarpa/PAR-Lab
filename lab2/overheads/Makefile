CC = gcc

OPENMP	 = -fopenmp
CFLAGS   = -Wall -O0 -std=c99 $(OPENMP)
CLIBS    = 
IINCL    = -I/usr/include/
ILIBS    = -lomptrace -L/usr/lib -lrt

TARGETS  = pi_seq pi_omp_parallel pi_omp_tasks pi_omp pi_omp_critical pi_omp_lock pi_omp_atomic pi_omp_sumvector pi_omp_padding 
all: $(TARGETS) 

pi_seq: pi_seq.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) 

pi_omp_parallel: pi_omp_parallel.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) 

pi_omp_tasks: pi_omp_tasks.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) 

pi_omp: pi_omp.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) 

pi_omp_critical: pi_omp_critical.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) 

pi_omp_lock: pi_omp_lock.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) 

pi_omp_atomic: pi_omp_atomic.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS)

pi_omp_sumvector: pi_omp_sumvector.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) 

pi_omp_padding: pi_omp_padding.c
	$(CC) $(CFLAGS) $< -o $@ $(CLIBS) 

clean:
	rm -rf $(TARGETS)

ultraclean:
	rm -rf $(TARGETS) TRACE*.mpit *.prv *.pcf *.row set-0 *.mpits *.o* *.e* *.txt
