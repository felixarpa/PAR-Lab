#!/bin/bash

USAGE="\n USAGE: run-xtr.sh PROG num_steps \n
        PROG       -> program name\n
        nun_steps  -> number of steps to compute pi\n"

if (test $# -lt 2 || test $# -gt 3)
then
        echo -e $USAGE
        exit 0
fi

export OMP_NUM_THREADS=4

export LD_PRELOAD=${EXTRAE_HOME}/lib/libomptrace.so
./$1 $2
unset LD_PRELOAD
#export LD_PRELOAD=""

mpi2prv -f TRACE.mpits -o $1_$2.prv -e $1 -paraver
rm -rf  TRACE.mpits set-0 >& /dev/null
