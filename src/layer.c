#include "../include/layer.h"
#include "../include/neuron.h"
#include <stdlib.h>

Layer *generate_random_layer(int *node_sizes, int size)
{

    Layer *l = (Layer *)malloc(sizeof(Layer));
    l->size = size;
    l->nodes = (Neuron **)malloc(size * sizeof(Neuron *));
    for (int i = 0; i < size; i++)
    {
        l->nodes[i] = generate_random_neuron(node_sizes[i]);
    }
    return l;
}

double *compute_layer_output(Layer *layer, double *inputs)
{
    double *out = (double *)malloc(layer->size * sizeof(double));
    for (int i = 0; i < layer->size; i++)
    {
        out[i] = compute_neuron_output(layer->nodes[i], inputs);
    }
    return out;
}

int layer_weights_number(Layer *layer)
{
    int sum = 0;
    for (int i = 0; i < layer->size; i++)
    {
        sum += layer->nodes[i]->size;
    }
    return sum;
}
