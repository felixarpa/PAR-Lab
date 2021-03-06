#!/bin/csh
# following option makes sure the job will run in the current directory
#$ -cwd
# following option makes sure the job has the same environmnent variables as the submission shell
#$ -V
# Canviar el nom del job
#$ -N lab2-omp

setenv SEQ  multisort
setenv PROG multisort-omp

# Make sure that all binaries exist
make $SEQ
make $PROG

setenv OMP_NUM_THREADS 8
setenv OMP_WAIT_POLICY "passive"

setenv size 32768
setenv merge_size 512
set sort_size_list = "1 2 4 8 16 32 64 128 256 512 1024 2048 4096"

set i = 1

set out = $PROG-$OMP_NUM_THREADS-sort_size.txt
rm -rf $out
rm -rf ./elapsed.txt
foreach sort_size ( $sort_size_list )
	echo $sort_size >> $out
	./$PROG $size $sort_size $merge_size >> $out
        set result = `cat $out | tail -n 4  | grep "Multisort execution time"| cut -d':' -f 2`
	echo $i >> ./elapsed.txt
	echo $result >> ./elapsed.txt
	set i = `echo $i + 1 | bc -l`
end

set i = 1
rm -rf ./hash_labels.txt
foreach sort_size ( $sort_size_list )
	echo "hash_label at " $i " : " $sort_size >> ./hash_labels.txt
	set i = `echo $i + 1 | bc -l`
end

jgraph -P depth-omp.jgr > $PROG-$OMP_NUM_THREADS-sort_size.ps
rm -rf ./hash_labels.txt
