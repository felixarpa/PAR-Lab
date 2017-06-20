
#!/bin/bash

#mv mandel-omp-10000--strong-omp.ps result/mandel-omp-10000-$1-$2-strong-omp.ps
mv mandel-omp-10000-8-schedule-omp.ps result/mandel-omp-10000-8-$1-$2-schedule-omp.ps
mv elapsed.txt result/elapsed-$1-$2.txt
mv speedup.txt result/speedup-$1-$2.txt
