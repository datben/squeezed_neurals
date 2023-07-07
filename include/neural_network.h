#include "./layer.h"

#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

typedef struct
{
    int nb_layer;
    int input_size;
    int output_size;
    Layer **layers;

} NeuralNetwork;

NeuralNetwork *generate_random_neural_network(int nb_layer, int *layer_sizes, int input_size);

double *compute_neural_network_output(const NeuralNetwork *nn, double *inputs);

#endif