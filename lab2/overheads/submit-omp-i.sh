#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V

make $1

setenv LD_PRELOAD ${EXTRAE_HOME}/lib/libomptrace.so
./$1 $2 $3 > $1_$2_$3.txt
setenv LD_PRELOAD 

mpi2prv -f TRACE.mpits -o $1_$2_$3.prv -e $1 -paraver
rm -rf TRACE.mpits TRACE.sym set-0 >& /dev/null
