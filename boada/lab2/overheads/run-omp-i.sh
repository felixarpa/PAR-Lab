#!/bin/bash

USAGE="\n USAGE: run-omp-i.sh PROG size n_th\n
        PROG   -> program name\n
        size   -> size of the problem\n
	n_th   -> number of threads\n"

if (test $# -lt 3 || test $# -gt 3)
then
        echo -e $USAGE
        exit 0
fi

export OMP_NUM_THREADS=$3

make $1

export LD_PRELOAD=${EXTRAE_HOME}/lib/libomptrace.so
./$1 $2 $3 > $1_$2_$3.txt
unset LD_PRELOAD
#export LD_PRELOAD=""

mpi2prv -f TRACE.mpits -o $1_$2_$3.prv -e $1 -paraver
rm -rf  TRACE.mpits set-0 >& /dev/null
