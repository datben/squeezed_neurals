#include "../include/layer.h"
#include "../include/neuron.h"

#include <iostream>

using namespace std;

Layer::Layer(int input_size, int nb_neurons)
{
    neurons = vector<Neuron *>(nb_neurons);
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
    vector<double> outputs = vector<double>(neurons.size());
    for (size_t i = 0; i < neurons.size(); i++)
    {
        outputs[i] = neurons[i]->feed_forward(inputs);
    }
    return outputs;
}

int Layer::get_nb_neurons() { return neurons.size(); }

vector<double> Layer::train(vector<double> inputs, vector<double> outputs, vector<double> errors, double learning_rate)
{
    vector<double> backward_errors(inputs.size(), 0);

    for (size_t i = 0; i < neurons.size(); i++)
    {

        vector<double> partial_backward_errors = neurons[i]->feed_backward(inputs, outputs[i], errors[i], learning_rate);

        double derivative_value = neurons[i]->activation_function->derivative(neurons[i]->merge_input(inputs));

        for (size_t j = 0; j < partial_backward_errors.size(); j++)
        {
            backward_errors[j] += partial_backward_errors[j] * derivative_value; // add * derivative of the activation function
        }
    }

    return backward_errors;
}
