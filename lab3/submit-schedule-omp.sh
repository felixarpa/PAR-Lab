#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V
# Canviar el nom del job
#$ -N lab1-omp

setenv SEQ  mandel
setenv PROG mandel-omp
setenv ITERS 10000

# Make sure that all binaries exist
make $SEQ
make $PROG

echo "Sequential execution" > $PROG.times.txt
echo "1" > ./elapsed.txt
/usr/bin/time -o ./elapsed.txt -a --format=%e ./$SEQ -i $ITERS >> $PROG.times.txt
set base = `cat ./elapsed.txt | tail -n 1`

setenv OMP_NUM_THREADS 8
set schedule_list = ""STATIC" "STATIC,10" "DYNAMIC,10" "GUIDED,10""
set i = 2

rm -rf ./speedup.txt
foreach schedule ( $schedule_list )
	setenv OMP_SCHEDULE `echo $schedule`
	echo $schedule >> $PROG.times.txt
	echo $i >> ./elapsed.txt
	/usr/bin/time -o ./elapsed.txt -a --format=%e ./$PROG -i $ITERS >> $PROG.times.txt
	set result = `cat ./elapsed.txt | tail -n 1`
	set speed = `echo $base/$result | bc -l`
	echo $i >> ./speedup.txt
	echo $speed >> ./speedup.txt
	set i = `echo $i + 1 | bc -l`
end

set i = 2
rm -rf ./hash_labels.txt
foreach schedule ( $schedule_list )
	echo "hash_label at " $i " : " $schedule >> ./hash_labels.txt
	set i = `echo $i + 1 | bc -l`
end

jgraph -P schedule-omp.jgr > $PROG-$ITERS-$OMP_NUM_THREADS-schedule-omp.ps
