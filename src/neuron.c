#include "../include/neuron.h"
#include "../include/math_utils.h"
#include <stdlib.h>

double compute_neuron_output(const Neuron *neuron, double *inputs)
{
    double res = 0;
    for (int i = 0; i < neuron->size; i++)
    {
        res += inputs[i] * neuron->weights[i];
    }
    return res;
}

Neuron *generate_random_neuron(int size)
{
    Neuron *n = (Neuron *)malloc(sizeof(Neuron));
    n->size = size;
    n->weights = (double *)malloc(size * sizeof(double));
    for (int i = 0; i < size; i++)
    {
        n->weights[i] = drand(-1.0, 1.0);
    }
    return n;
}