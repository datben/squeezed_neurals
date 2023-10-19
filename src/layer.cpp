#include "../include/layer.h"
#include "../include/neuron.h"

#include <iostream>

using namespace std;

Layer::Layer(int input_size, int nb_neurons)
{
    neurons.reserve(nb_neurons);
    for (int i = 0; i < nb_neurons; i++)
    {
        neurons[i] = new Neuron(input_size);
    }
}

Layer::~Layer()
{
}

vector<double> Layer::feed_forward(vector<double> inputs)
{
    vector<double> outputs;
    outputs.reserve(neurons.size());
    for (int i = 0; i < neurons.size(); i++)
    {
        outputs[i] = neurons[i]->feed_forward(inputs);
    }
    return outputs;
}

int Layer::get_nb_neurons() { return neurons.size(); }

vector<double> Layer::train(vector<double> inputs, vector<double> outputs, vector<double> errors, double learning_rate)
{
    vector<double> backward_errors(neurons.size(), 0);

    for (int i = 0; i < neurons.size(); i++)
    {
        vector<double> partial_backward_errors = neurons[i]->feed_backward(inputs, outputs[i], errors[i], learning_rate);

        for (int j = 0; j < partial_backward_errors.size(); j++)
        {
            backward_errors[j] += partial_backward_errors[j]; // add * derivative of the activation function
        }
    }

    return backward_errors;
}
