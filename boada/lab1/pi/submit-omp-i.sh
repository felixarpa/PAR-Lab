#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V

setenv PROG pi_omp_i
make $PROG

setenv size 100000000

#setenv OMP_NUM_THREADS 1
setenv OMP_NUM_THREADS 8

setenv LD_PRELOAD ${EXTRAE_HOME}/lib/libomptrace.so
./$PROG $size
setenv LD_PRELOAD 

mpi2prv -f TRACE.mpits -o ${PROG}_${size}_${OMP_NUM_THREADS}.prv -e $PROG -paraver
rm -rf TRACE.mpits TRACE.sym set-0 >& /dev/null
