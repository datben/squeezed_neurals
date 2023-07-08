#include "../include/neural_network.h"
#include "../include/layer.h"
#include "../include/math_utils.h"
#include <stdlib.h>

NeuralNetwork *generate_random_neural_network(int nb_layer, const int *layer_sizes, int input_size)
{
    NeuralNetwork *nn = (NeuralNetwork *)malloc(sizeof(NeuralNetwork));
    nn->nb_layer = nb_layer;
    nn->input_size = input_size;
    nn->layer_sizes = layer_sizes;
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

double **compute_neural_network_output(const NeuralNetwork *nn, double *inputs)
{

    double *input = inputs;
    double **outputs = (double **)malloc(nn->nb_layer * sizeof(double *));
    for (int i = 0; i < nn->nb_layer; i++)
    {
        input = compute_layer_output(nn->layers[i], input);
        outputs[i] = input;
    }
    return outputs;
}

double ***compute_neural_network_error_n(const NeuralNetwork *nn, const double *inputs, const double **nn_outputs, const double *expected_output)
{
    double ***err_n = (double ***)malloc(nn->nb_layer * sizeof(double **));
    int output_size = nn->output_size;
    double *output_err = sub_vec(nn_outputs[nn->nb_layer - 1], expected_output, output_size);

    for (int i = nn->nb_layer - 1; i >= 0; i--)
    {
        err_n[i] = (double **)malloc(nn->layer_sizes[i] * sizeof(double *));

        int input_size;
        const double *input;

        if (i == 0)
        {
            input_size = nn->input_size;
            input = inputs;
        }
        else
        {
            input_size = nn->layer_sizes[i - 1];
            input = nn_outputs[i - 1];
        }

        for (int j = 0; j < nn->layer_sizes[i]; j++)
        {
            err_n[i][j] = (double *)malloc(input_size * sizeof(double));
            for (int k = 0; k < input_size; k++)
            {
                err_n[i][j][k] = output_err[j] * input[k];
            }
        }

        int temp_output_size = nn->layer_sizes[i];
        double *temp_output_err = (double *)malloc(temp_output_size * sizeof(double));

        for (int j = 0; j < output_size; j++)
        {
            double sum = 0;
            for (int k = 0; k < output_size; k++)
            {
                sum += nn->layers[i]->nodes[k]->weights[j] * output_err[k];
            }
            temp_output_err[j] = sum;
        }

        free(output_err);

        output_err = temp_output_err;
        output_size = temp_output_size;
    }
    return err_n;
}

int neural_network_weights_number(const NeuralNetwork *nn)
{
    int sum = nn->input_size * nn->layer_sizes[0];
    for (int i = 1; i < nn->nb_layer; i++)
    {
        sum += nn->layer_sizes[i - 1] * nn->layer_sizes[i];
    }
    return sum;
}

void backpropagation_update(const NeuralNetwork *nn, double learning_rate, int nb_inputs, const double **inputs, const double ***nn_outputs, const double **expected_output)
{

    const double ***err = (double ***)malloc(neural_network_weights_number(nn) * sizeof(double));
    for (int n = 0; n < nb_inputs; n++)
    {
        double ***err_n = compute_neural_network_error_n(nn, inputs[n], nn_outputs[n], expected_output[n]);
        for (int i = 0; i < nn->nb_layer; i++)
        {
            for (int j = 0; j < nn->layer_sizes[i]; j++)
            {
                Layer *layer = nn->layers[i];

                for (int k = 0; k < layer->size; k++)
                {
                    double *temp = add_vec(err[i][i][k], err_n, layer->nodes[k]->size);
                }
            }
        }
    }
}