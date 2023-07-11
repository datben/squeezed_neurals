#include "../include/neural_network.h"
#include "../include/layer.h"
#include "../include/math_utils.h"
#include <stdlib.h>
#include <stdio.h>

NeuralNetwork *generate_random_neural_network(int nb_layer, int *layer_sizes, int input_size)
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

double **compute_neural_network_last_and_hidden_outputs(NeuralNetwork *nn, double *inputs)
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

double *compute_neural_network_last_output(NeuralNetwork *nn, double *inputs)
{

    double *input = inputs;
    for (int i = 0; i < nn->nb_layer; i++)
    {
        double *temp = compute_layer_output(nn->layers[i], input);
        if (i != 0)
        {
            free(input);
        }
        input = temp;
    }
    return input;
}

double ***compute_neural_network_partial_derivate_error_n(NeuralNetwork *nn, double *inputs, double **nn_outputs, double *expected_output)
{
    double ***err_n = (double ***)malloc(nn->nb_layer * sizeof(double **));

    // output loss
    double *output_err = sub_vec(nn_outputs[nn->nb_layer - 1], expected_output, nn->output_size);

    int input_size;
    double *input;

    // i index in layers
    for (int i = nn->nb_layer - 1; i >= 0; i--)
    {

        Layer *layer = nn->layers[i];
        err_n[i] = (double **)malloc(layer->size * sizeof(double *));

        if (i == 0)
        {
            // input of neuron 0 is input of the network
            input_size = nn->input_size;
            input = inputs;
        }
        else
        {
            // output on neuron N is input of neuron N+1
            input_size = nn->layer_sizes[i - 1];
            input = nn_outputs[i - 1];
        }

        // compute dEn/dWjk
        // j index on neuron
        for (int j = 0; j < layer->size; j++)
        {
            err_n[i][j] = (double *)malloc(input_size * sizeof(double));
            // k index on neuron weights
            for (int k = 0; k < input_size; k++)
            {
                err_n[i][j][k] = output_err[j] * input[k];
            }
        }

        double *temp_output_err = (double *)malloc(layer->size * sizeof(double));

        // backprogate loss for each neuron (no activation fn for now)
        // j index on neuron of layer i-1
        for (int j = 0; j < input_size; j++)
        {
            double sum = 0;
            // k index on neuron of layer i
            for (int k = 0; k < layer->size; k++)
            {
                sum += layer->nodes[k]->weights[j] * output_err[k];
            }
            temp_output_err[j] = sum;
        }

        free(output_err);
        output_err = temp_output_err;
    }
    free(output_err);
    return err_n;
}

int neural_network_weights_number(NeuralNetwork *nn)
{
    int sum = 0;
    for (int i = 1; i < nn->nb_layer; i++)
    {
        sum += layer_weights_number(nn->layers[i]);
    }
    return sum;
}

void backpropagation_update(NeuralNetwork *nn, double learning_rate, int nb_inputs, double **inputs, double ***nn_outputs, double **expected_output)
{

    double ***err = compute_neural_network_partial_derivate_error_n(nn, inputs[0], nn_outputs[0], expected_output[0]);
    for (int n = 1; n < nb_inputs; n++)
    {
        double ***err_n = compute_neural_network_partial_derivate_error_n(nn, inputs[n], nn_outputs[n], expected_output[n]);
        for (int i = 0; i < nn->nb_layer; i++)
        {
            for (int j = 0; j < nn->layer_sizes[i]; j++)
            {
                int size = layer_weights_number(nn->layers[i]);
                double *temp1 = add_vec(err_n[i][j], err[i][j], size);
                double *temp2 = mul_vec(err_n[i][j], 1.0 / ((double)nb_inputs), size);

                err[i][j] = temp2;

                free(temp1);
                free(err_n[i][j]);
            }
            free(err_n[i]);
        }
        free(err_n);
    }

    for (int i = 0; i < nn->nb_layer; i++)
    {
        Layer *layer = nn->layers[i];
        for (int j = 0; j < layer->size; j++)
        {
            Neuron *neuron = layer->nodes[j];
            for (int k = 0; k < neuron->size; k++)
            {
                neuron->weights[k] -= err[i][j][k];
            }
            free(err[i][j]);
        }
        free(err[i]);
    }
    free(err);
}

void train_neural_network(NeuralNetwork *nn, double learning_rate, int nb_epoch, int nb_inputs, double **inputs, double **expected_output)
{

    double ***outputs = (double ***)malloc(nb_inputs * sizeof(double **));
    for (int n = 0; n < nb_epoch; n++)
    {

        printf("Epoch %i\n", n);

        for (int i = 0; i < nb_inputs; i++)
        {
            outputs[i] = compute_neural_network_last_and_hidden_outputs(nn, inputs[i]);
        }
        backpropagation_update(nn, learning_rate, nb_inputs, inputs, outputs, expected_output);
        for (int i = 0; i < nb_inputs; i++)
        {
            for (int j = 0; j < nn->nb_layer; j++)
            {
                free(outputs[i][j]);
            }
            free(outputs[i]);
        }
    }
    free(outputs);
}
