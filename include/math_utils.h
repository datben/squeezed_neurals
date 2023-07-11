#ifndef MATHUTILS
#define MATHUTILS

double drand(double low, double high);

void init_rand(void);

double euclidean_norm(double *vec, int dim);

double *add_vec(double *a, double *b, int dim);

double *sub_vec(double *a, double *b, int dim);

double *mul_vec(double *vec, double scalar, int dim);

#endif