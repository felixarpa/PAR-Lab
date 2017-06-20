#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V
# Canviar el nom del job
#$ -N lab1-omp

setenv PROG mandel-omp
make $PROG

setenv OMP_NUM_THREADS 8
setenv OMP_SCHEDULE "STATIC"

setenv LD_PRELOAD ${EXTRAE_HOME}/lib/libomptrace.so
./$PROG -i 10000
setenv LD_PRELOAD 

mpi2prv -f TRACE.mpits -o ${PROG}_${OMP_NUM_THREADS}_${OMP_SCHEDULE}.prv -e $PROG -paraver
rm -rf TRACE.mpits TRACE.sym set-0
