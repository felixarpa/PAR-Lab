.SUFFIXES: .omp
#CC       = gcc-mp-4.6
CC       = gcc

OPENMP   = -fopenmp
CFLAGS   = -g -Wall -O3 $(OPENMP) -fno-inline -I.  
CLIBS    = 

TARGET  = 1.for 2.schedule 3.nowait 4.collapse 5.ordered 6.doacross 
OBJECTS	= $(TARGET)

program:	$(TARGET)

.c.omp:
	$(CC) $< $(CFLAGS) -o $@ -I. -L. $(CLIBS) -lm

1.for: 1.for.c
	$(CC) $< $(CFLAGS) -o $@ -I. -L. $(CLIBS) -lm

2.schedule: 2.schedule.c
	$(CC) $< $(CFLAGS) -o $@ -I. -L. $(CLIBS) -lm

3.nowait: 3.nowait.c
	$(CC) $< $(CFLAGS) -o $@ -I. -L. $(CLIBS) -lm

4.collapse: 4.collapse.c
	$(CC) $< $(CFLAGS) -o $@ -I. -L. $(CLIBS) -lm

5.ordered: 5.ordered.c
	$(CC) $< $(CFLAGS) -o $@ -I. -L. $(CLIBS) -lm

6.doacross: 6.doacross.c
	$(CC) $< $(CFLAGS) -o $@ -I. -L. $(CLIBS) -lm

clean:
	rm -f $(OBJECTS)
