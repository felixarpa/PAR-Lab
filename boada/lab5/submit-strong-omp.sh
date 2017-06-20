#!/bin/bash
### Directives pel gestor de cues
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V
# Canviar el nom del job
#$ -N lab13omp
# Per canviar de shell
#$ -S /bin/bash

SEQ=heat
PROG=heat-omp
np_NMIN=1
np_NMAX=12
N=2

# Make sure that all binaries exist
make $SEQ
make $PROG

out=$PROG-strong.txt	# File where you save the execution results
aux=./tmp.txt     	# archivo auxiliar

outputpath=./elapsed.txt
outputpath2=./speedup.txt
rm -rf $outputpath 2> /dev/null
rm -rf $outputpath2 2> /dev/null

echo Executing $SEQ sequentially >> $out
elapsed=0  # Acumulacion del elapsed time de las N ejecuciones del programa
i=0        # Variable contador de repeticiones
while (test $i -lt $N)
	do
		echo $'\n' >> $out
		/usr/bin/time --format=%e ./$SEQ test.dat >> $out 2>$aux

		time=`cat $aux|tail -n 1`
			
		elapsed=`echo $elapsed + $time|bc`
			
		i=`expr $i + 1`
	done
echo $'\n' >> $out
echo -n ELAPSED TIME AVERAGE OF $N EXECUTIONS = >> $out
sequential=`echo $elapsed/$N|bc -l`
echo $sequential >> $out

i=0
PARS=$np_NMIN
while (test $PARS -le $np_NMAX)
do
	echo $'\n' >> $out
	echo -n Executing $PROG in parallel with $PARS threads >> $out
	elapsed=0  # Acumulacion del elapsed time de las N ejecuciones del programa

	while (test $i -lt $N)
		do
			echo $'\n' >> $out
                        export OMP_NUM_THREADS=$PARS
			/usr/bin/time --format=%e ./$PROG test.dat >> $out 2>$aux

			time=`cat $aux|tail -n 1`
			
			elapsed=`echo $elapsed + $time|bc`
			
			rm -f $aux
			i=`expr $i + 1`
		done

	echo $'\n' >> $out
	echo -n ELAPSED TIME AVERAGE OF $N EXECUTIONS = >> $out
    	average=`echo $elapsed/$N|bc -l`
    	result=`echo $sequential/$average|bc -l`
    	echo $average >> $out

	i=0

    	#output PARS i average en fichero elapsed time
	echo -n $PARS >> $outputpath
	echo -n "   " >> $outputpath
    	echo $average >> $outputpath

    	#output PARS i average en fichero speedup
	echo -n $PARS >> $outputpath2
	echo -n "   " >> $outputpath2
    	echo $result >> $outputpath2

    	#incrementa el parametre
	PARS=`expr $PARS + 1`
done

jgraph -P strong-omp.jgr >  $PROG-strong.ps
