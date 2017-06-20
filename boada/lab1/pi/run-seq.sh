#!/bin/bash

USAGE="\n USAGE: run-seq.sh PROG size\n
        PROG    -> sequential program name \n
	size    -> size of the problem\n"

#Parameters
if (test $# -lt 2 || test $# -gt 2)
then
	echo -e $USAGE
	exit 0					
fi		

/usr/bin/time ./$1 $2
