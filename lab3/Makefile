# C compiler
OMPC    = gcc
OPT3 	= -O3
OPTG0 	= -g -O0
CFLAGS  = -std=c99 #-Wall -std=c99
OPENMP	= -fopenmp
LFLAGS  = -lX11 -L/usr/X11R6/lib 
CINCL    = -I.
CLIBS    = -L.

# Tareador compiler
TAREADORCC = tar-clang
TAREADOR_FLAGS = -tareador-lite -isystem/scratch/nas/1/par0/Soft

TARGETS  = mandel mandeld mandel-tareador mandeld-tareador mandel-omp mandeld-omp
all: $(TARGETS)

mandel:	mandel-serial.c
	$(OMPC) -o $@ $(OPT3) $(CFLAGS) $^ 

mandeld: mandel-serial.c
	$(OMPC) -D_DISPLAY_ -o $@ $(OPT3) $(CFLAGS) $^ $(LFLAGS)

mandel-tareador: mandel-tareador.c
	$(TAREADORCC) $(OPTG0) $(TAREADOR_FLAGS) $(CFLAGS) $(CINCL) $< -o $@ $(CLIBS) 

mandeld-tareador: mandel-tareador.c
	$(TAREADORCC) -D_DISPLAY_ $(OPTG0) $(TAREADOR_FLAGS) $(CFLAGS) $(CINCL) $< -o $@ $(CLIBS) $(LFLAGS)

mandel-omp: mandel-omp.c
	$(OMPC) -o $@ $(OPT3) $(CFLAGS) $(OPENMP) $^ 

mandeld-omp: mandel-omp.c
	$(OMPC) -D_DISPLAY_ -o $@ $(OPT3) $(CFLAGS) $(OPENMP) $^ $(LFLAGS)

clean:
	rm -rf $(TARGETS) .tareador_precomputed* logs *.log

ultraclean:
	rm -rf $(TARGETS) .tareador_precomputed* logs *.log *.prv *.pcf *.row dependency_graph* *.times.txt *lab1-omp.e* *lab1-omp.o* elapsed.txt speedup.txt hash_labels.txt TRACE.sym TRACE.mpits set-0 *.ps
