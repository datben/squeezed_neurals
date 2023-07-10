#include "./layer.h"

#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

typedef struct
{
    int nb_layer;
    int input_size;
    int output_size;
    const int *layer_sizes;
    Layer **layers;

} NeuralNetwork;

NeuralNetwork *generate_random_neural_network(int nb_layer, const int *layer_sizes, int input_size);

double **compute_neural_network_output(const NeuralNetwork *nn, double *inputs);

double ***compute_neural_network_partial_derivate_error_n(const NeuralNetwork *nn, const double *inputs, const double **nn_outputs, const double *expected_output);

void backpropagation_update(const NeuralNetwork *nn, double learning_rate, int nb_inputs, const double **inputs, const double ***nn_outputs, const double **expected_output);

int neural_network_weights_number(const NeuralNetwork *nn);

void train_neural_network(const NeuralNetwork *nn, double learning_rate, int nb_epoch, int nb_inputs, const double **inputs, const double **expected_output);

#endif