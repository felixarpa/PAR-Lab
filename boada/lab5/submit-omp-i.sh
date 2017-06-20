#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V
# Canviar el nom del job
#$ -N lab3-omp

setenv PROG heat-omp
make $PROG

setenv OMP_NUM_THREADS 8

setenv LD_PRELOAD ${EXTRAE_HOME}/lib/libomptrace.so
./$PROG test.dat > ${PROG}_${OMP_NUM_THREADS}.times.txt
setenv LD_PRELOAD 

mpi2prv -f TRACE.mpits -o ${PROG}_${OMP_NUM_THREADS}.prv -e $PROG -paraver
rm -rf TRACE.mpits TRACE.sym set-0
