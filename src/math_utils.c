#include "../include/math_utils.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void init_rand(void)
{
    srand((int)time(NULL));
}

double drand(double low, double high)
{
    return ((double)rand() * (high - low)) / (double)RAND_MAX + low;
}
