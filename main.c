#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <omp.h>

#include "pi.h"

int n;
int p;
bool over_p = false;

int main(int argc, char *argv[])
{
	double pi, runtime;
	struct timeval t1, t2;
	double true_pi = 3.14159265358979;

	assert(argc >= 4);

	n = atoi(argv[1]);
	p = atoi(argv[2]);
	if (argv[3][0] == 'y') {
		printf("over p\n");
		over_p = true;
	}
	else {
		printf("not over p\n");
		over_p = false;
	}

	omp_set_num_threads(p);

	gettimeofday(&t1, NULL);
	pi = estimate_pi();
	gettimeofday(&t2, NULL);

	runtime = (t2.tv_sec-t1.tv_sec) +
	    ((double) t2.tv_usec-t1.tv_usec)/1000000;

	printf("Estimate: %.20lf\n", pi);
	printf("Difference: %.20lf\n", pi-true_pi);
	printf("Runtime: %lf s\n", runtime);

	return 0;
}
