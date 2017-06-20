TAREADORCC = tareador-clang
TAREADOR_FLAGS = -tareador-lite

CFLAGS  = -Wall -fno-inline -march=native -ffloat-store 
OPTG0   = -g -O0

CINCL   = -I. -I${FFTW3_HOME}/include
CLIBS   = -L. ${FFTW3_HOME}/lib/libfftw3f.a -lm

TARGETS  = 3dfft_seq 3dfft_v1 3dfft_v2 3dfft_v3 3dfft_v4
all: $(TARGETS) 

3dfft_seq:	3dfft_seq.c constants.h
	$(TAREADORCC) $(CFLAGS) $(OPTG0) $(CINCL) $< -o $@ $(CLIBS) $(TAREADOR_FLAGS)

3dfft_v1:	3dfft_v1.c constants.h
	$(TAREADORCC) $(CFLAGS) $(OPTG0) $(CINCL) $< -o $@ $(CLIBS) $(TAREADOR_FLAGS)

3dfft_v2:	3dfft_v2.c constants.h
	$(TAREADORCC) $(CFLAGS) $(OPTG0) $(CINCL) $< -o $@ $(CLIBS) $(TAREADOR_FLAGS)

3dfft_v3:	3dfft_v3.c constants.h
	$(TAREADORCC) $(CFLAGS) $(OPTG0) $(CINCL) $< -o $@ $(CLIBS) $(TAREADOR_FLAGS)

3dfft_v4:	3dfft_v4.c constants.h
	$(TAREADORCC) $(CFLAGS) $(OPTG0) $(CINCL) $< -o $@ $(CLIBS) $(TAREADOR_FLAGS)

clean:
	rm -rf $(TARGETS)

ultraclean:
	rm -rf $(TARGETS) .tareador_precomputed_* logs *.log *.prv *.pcf *.raw dependency_graph*
