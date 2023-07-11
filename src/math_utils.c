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

double euclidean_norm( double *vec, int dim)
{
    double output = 0.0;
    for (int i = 0; i < dim; i++)
    {
        output += pow(vec[i], 2);
    }
    return sqrt(output);
}

double *add_vec( double *a,  double *b, int dim)
{
    double *output = (double *)malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++)
    {
        output[i] = a[i] + b[i];
    }
    return output;
}

double *sub_vec( double *a,  double *b, int dim)
{
    double *output = (double *)malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++)
    {
        output[i] = a[i] - b[i];
    }
    return output;
}

double *mul_vec( double *vec, double scalar, int dim)
{
    double *output = (double *)malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++)
    {
        output[i] = vec[i] * scalar;
    }
    return output;
}