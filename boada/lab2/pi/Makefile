.SUFFIXES: -omp -debug
CC       = gcc

OPENMP	 = -fopenmp
CFLAGS   = -Wall -std=c99 -O3 $(OPENMP) -fno-inline -I.  
CLIBS    = -L. -lm

.c-debug:
	$(CC) -D_DEBUG_ $< $(CFLAGS) -o $@ $(CLIBS) 

.c-omp:
	$(CC) $< $(CFLAGS) -o $@ $(CLIBS) 

clean:
	rm -f *-omp *-debug *.prv *.row *.pcf
