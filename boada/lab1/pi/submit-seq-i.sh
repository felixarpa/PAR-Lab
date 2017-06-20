#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V

setenv PROG pi_seq_i
make $PROG

setenv size 100000000
setenv OMP_NUM_THREADS 1

setenv LD_PRELOAD ${EXTRAE_HOME}/lib/libomptrace.so
./$PROG $size
setenv LD_PRELOAD 

mpi2prv -f TRACE.mpits -o ${PROG}_${size}.prv -e $PROG -paraver
rm -rf  TRACE.mpits set-0 >& /dev/null
