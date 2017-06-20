TAREADORCC = tareador-clang
TAREADOR_FLAGS = -tareador-lite

OPTG0   = -g -O0

INCL    = -I.
LIBS    = -L.

TARGETS  = dot_product
all: $(TARGETS) 

dot_product:	dot_product.c
	$(TAREADORCC) $(OPTG0) $(INCL) $< -o $@ $(LIBS) $(TAREADOR_FLAGS)

clean:
	rm -rf $(TARGETS)

ultraclean:
	rm -rf $(TARGETS) .tareador_precomputed_* logs *.log *.prv *.pcf *.raw dependency_graph*
