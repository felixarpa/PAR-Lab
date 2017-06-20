CC = gcc
OPENMP	 = -fopenmp 
CFLAGS   = -Wall -O3 -std=c99 -march=native
# Needed if user events are introduced in source file
IINCL    = -I${EXTRAE_HOME}/include/
ILIBS    = -L$(EXTRAE_HOME)/lib -lomptrace

TARGETS  = pi_seq pi_omp pi_seq_i pi_omp_i
all: $(TARGETS) 

pi_seq: pi_seq.c
	$(CC) $(CFLAGS) $< -o $@

pi_omp: pi_omp.c
	$(CC) $(CFLAGS) $(OPENMP) $< -o $@

# Need to compile/link with library if user events are used
pi_seq_i: pi_seq.c
	$(CC) -D_EXTRAE_ $(CFLAGS) $(OPENMP) $(IINCL) $< -o $@ $(ILIBS)

# Need to compile/link with library if user events are used
pi_omp_i: pi_omp.c
	$(CC) -D_EXTRAE_ $(CFLAGS) $(OPENMP) $(IINCL) $< -o $@ $(ILIBS)

clean:
	rm -rf $(TARGETS)

ultraclean:
	rm -rf TRACE*.mpit $(TARGETS) *.prv *.pcf *.row set-0 *.mpits *.sym *.o* *.e* *.txt *.ps *.pdf
