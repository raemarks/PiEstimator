all:
	gcc -g -Wall -lm -fopenmp -o omp_pi main.c pi.c

runSpeedup:
	./omp_pi 500000000 1 n
	./omp_pi 500000000 2 n
	./omp_pi 500000000 3 n
	./omp_pi 500000000 4 n

runPrecision:
	./omp_pi 1000000000 1 y
	./omp_pi 1000000000 2 y
	./omp_pi 1000000000 3 y
	./omp_pi 1000000000 4 y
	./omp_pi 1000000000 5 y
	./omp_pi 1000000000 6 y
	./omp_pi 1000000000 7 y
	./omp_pi 1000000000 8 y
	./omp_pi 1000000000 9 y
	./omp_pi 1000000000 10 y
	./omp_pi 1000000000 11 y
	./omp_pi 1000000000 12 y
	./omp_pi 1000000000 13 y
	./omp_pi 1000000000 14 y
	./omp_pi 1000000000 15 y
	./omp_pi 1000000000 16 y
#run:
#	mpiexec -machinefile ./machinefile.txt -n 1 ./a.out 80 10 23 87 5 "junk.csv" test
#	rm -rf junk.csv
#
send:
	rsync main.c pi.c mp_constants.h pi.h Makefile rmarks@ssh1.eecs.wsu.edu:/net/u/rmarks/pvt/
#
#test:
#	./run_tests.sh
