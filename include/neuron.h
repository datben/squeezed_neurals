#ifndef NEURON
#define NEURON

typedef struct
{
    int size;
    double *weights;
    double bias;
} Neuron;

double compute_neuron_output(const Neuron *neuron, double *inputs);

Neuron *generate_random_neuron(int size);

#endif