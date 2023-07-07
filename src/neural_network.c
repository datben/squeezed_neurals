#include "../include/neural_network.h"
#include "../include/layer.h"
#include <stdlib.h>

NeuralNetwork *generate_random_neural_network(int nb_layer, int *layer_sizes, int input_size)
{
    NeuralNetwork *nn = (NeuralNetwork *)malloc(sizeof(NeuralNetwork));
    nn->nb_layer = nb_layer;
    nn->input_size = input_size;
    nn->output_size = layer_sizes[nb_layer - 1];
    nn->layers = (Layer **)malloc(nb_layer * sizeof(Layer *));
    int input = input_size;
    for (int i = 0; i < nb_layer; i++)
    {
        int *nodes_sizes = (int *)malloc(layer_sizes[i] * sizeof(int));
        for (int j = 0; j < layer_sizes[i]; j++)
        {
            nodes_sizes[j] = input;
        }
        nn->layers[i] = generate_random_layer(nodes_sizes, layer_sizes[i]);
        free(nodes_sizes);
        input = layer_sizes[i];
    }
    return nn;
}

double *compute_neural_network_output(const NeuralNetwork *nn, double *inputs)
{

    double *outputs = inputs;
    for (int i = 0; i < nn->nb_layer; i++)
    {
        outputs = compute_layer_output(nn->layers[i], outputs);
    }
    return outputs;
}