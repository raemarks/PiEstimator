#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>

#include "mp_constants.h"
#include "pi.h"

const double center_x = 0.5;
const double center_y = 0.5;

#define HUGE_PRIME 217645177

bool
in_circle(double x, double y)
{
	double distance = 0;

	distance = (x-center_x)*(x-center_x) + (y-center_y)*(y-center_y);
	distance = sqrt(distance);

	if (distance <= 0.5)
		return true;

	return false;
}

double
estimate_pi()
{
	int rank;
	uint64_t inside = 0, i;
	uint64_t it = n;
	double x, y;
	struct drand48_data myseed;

	if (over_p)
		it*=p;
	printf("it: %ld\n", it);

#pragma omp parallel default(none) \
	private(i, myseed, x, y, rank) shared(inside, n, it, p, over_p)
	{
		rank = omp_get_thread_num();
		srand48_r(rank*HUGE_PRIME + time(NULL), &myseed);

#pragma omp for reduction(+:inside)
		for (i = 0; i < it; i++) {
			drand48_r(&myseed, &x);
			drand48_r(&myseed, &y);

			if (in_circle(x, y)) {
				inside++;
			}
		}
	}

	return (((double)inside)/it)*4;
}
