#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>

#include "mp_constants.h"
#include "pi.h"


#define HUGE_PRIME 217645177

bool
in_circle(double x, double y)
{
	const double center_x = 0.5;
	const double center_y = 0.5;
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
	uint64_t result = 0;
#pragma omp parallel
	{
		/* These variables are private */
		int rank = omp_get_thread_num();
		uint64_t inside = 0, i;
		uint64_t it = n;
		double x, y;
		struct drand48_data myseed;
		srand48_r(rank*HUGE_PRIME, &myseed);

		/* n fixed, not n/p fixed. */
		if (!over_p) {
			it /= p;
		}

		for (i = 0; i < it; i++) {
			drand48_r(&myseed, &x);
			drand48_r(&myseed, &y);

			if (in_circle(x, y)) {
				inside++;
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
