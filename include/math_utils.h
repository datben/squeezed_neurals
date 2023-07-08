#ifndef MATHUTILS
#define MATHUTILS

double drand(double low, double high);

void init_rand(void);

double euclidean_norm(const double *vec, int dim);

double *add_vec(const double *a, const double *b, int dim);

double *sub_vec(const double *a, const double *b, int dim);

double *mul_vec(const double *vec, double scalar, int dim);

#endif