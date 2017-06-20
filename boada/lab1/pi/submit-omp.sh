#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V

setenv PROG pi_omp
make $PROG

setenv size 1000000000

#setenv OMP_NUM_THREADS 1
setenv OMP_NUM_THREADS 8

/usr/bin/time -o ${PROG}_time.txt ./$PROG $size
