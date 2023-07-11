#include "./layer.h"

#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

typedef struct
{
    int nb_layer;
    int input_size;
    int output_size;
    int *layer_sizes;
    Layer **layers;

} NeuralNetwork;

NeuralNetwork *generate_random_neural_network(int nb_layer, int *layer_sizes, int input_size);

double **compute_neural_network_last_and_hidden_outputs(NeuralNetwork *nn, double *inputs);

double *compute_neural_network_last_output(NeuralNetwork *nn, double *inputs);

double ***compute_neural_network_partial_derivate_error_n(NeuralNetwork *nn, double *inputs, double **nn_outputs, double *expected_output);

void backpropagation_update(NeuralNetwork *nn, double learning_rate, int nb_inputs, double **inputs, double ***nn_outputs, double **expected_output);

int neural_network_weights_number(NeuralNetwork *nn);

void train_neural_network(NeuralNetwork *nn, double learning_rate, int nb_epoch, int nb_inputs, double **inputs, double **expected_output);

#endif