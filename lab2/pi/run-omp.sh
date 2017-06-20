#!/bin/bash

USAGE="\n USAGE: run-omp.sh PROG num_steps \n
        PROG       -> program name\n
        nun_steps  -> number of steps to compute pi\n"

if (test $# -lt 2 || test $# -gt 3)
then
        echo -e $USAGE
        exit 0
fi

export OMP_NUM_THREADS=4

#/usr/bin/time ./$1 $2
./$1 $2
