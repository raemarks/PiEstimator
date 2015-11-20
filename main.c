#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include <omp.h>

#include "pi.h"

int n;
int p;
bool over_p;

int main(int argc, char *argv[])
	//TODO: make sure to use the omp time thing.
{
	double pi, runtime;
	struct timeval t1, t2;

	assert(argc >= 4);

	n = atoi(argv[1]);
	p = atoi(argv[2]);
	if (argv[3][0] == 'y')
		over_p = true;

	omp_set_num_threads(p);

	gettimeofday(&t1, NULL);
	pi = estimate_pi();
	gettimeofday(&t2, NULL);

	runtime = (t2.tv_sec-t1.tv_sec)*1000 +
	    ((double) t2.tv_usec-t1.tv_usec)/1000;

	printf("Estimate: %.20lf\n", pi);
	printf("Runtime: %lf ms\n", runtime);

	return 0;
}
