#include "./neuron.h"

#ifndef LAYER
#define LAYER

typedef struct
{
    int size;
    Neuron **nodes;

} Layer;

Layer *generate_random_layer(int *node_sizes, int size);

double *compute_layer_output(const Layer *layer, double *inputs);

#endif