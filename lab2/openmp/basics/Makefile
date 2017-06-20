CC       = gcc

OPENMP	 = -fopenmp
CFLAGS   = -Wall -O3 -fno-inline $(OPENMP)

TARGET   = 1.hello 2.hello 2.hello_shared 2.hello_private 2.hello_firstprivate 3.how_many 4.data_sharing 5.parallel 6.datarace 7.barrier

program: $(TARGET)

1.hello: 1.hello.c
	$(CC) $(CFLAGS) -o $@ $<

2.hello: 2.hello.c
	$(CC) $(CFLAGS) -o $@ $<

2.hello_shared: 2.hello_shared.c
	$(CC) $(CFLAGS) -o $@ $<

2.hello_private: 2.hello_private.c
	$(CC) $(CFLAGS) -o $@ $<

2.hello_firstprivate: 2.hello_firstprivate.c
	$(CC) $(CFLAGS) -o $@ $<

3.how_many: 3.how_many.c
	$(CC) $(CFLAGS) -o $@ $<

4.data_sharing: 4.data_sharing.c
	$(CC) $(CFLAGS) -o $@ $<

5.parallel: 5.parallel.c
	$(CC) $(CFLAGS) -o $@ $<

6.datarace: 6.datarace.c
	$(CC) $(CFLAGS) -o $@ $<

7.barrier: 7.barrier.c
	$(CC) $(CFLAGS) -o $@ $<

clean: 
	rm -f $(TARGET)
