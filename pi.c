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
rand_double(unsigned int *seed)
{
	/* Return a random number in the range [0.0,1.0] */
	return (double)rand_r(seed)/(double)(RAND_MAX);
}

double
estimate_pi()
{
	uint64_t result = 0;
#pragma omp parallel
	{
		/* These variables are private */
		int rank = omp_get_thread_num();
		uint64_t inside = 0, i;
		uint64_t it = n;
		double x, y;
		unsigned int myseed = rank*HUGE_PRIME + time(NULL);

		/* n fixeed, not n/p fixed. */
		if (!over_p)
			it /= p;

		for (i = 0; i < it; i++) {
			x = rand_double(&myseed);
			y = rand_double(&myseed);

			if (in_circle(x, y)) {
				inside++;
			}
			if (inside < 0) {
				printf("OVERFLOW! Iteration %ld\n", i);
			}
		}
#pragma omp critical
		{
			result += inside;
		}
	}

	if (over_p)
		return (((double)result)/((uint64_t)n*(uint64_t)p))*4;
	else
		return (((double)result)/(uint64_t)n)*4;
}
