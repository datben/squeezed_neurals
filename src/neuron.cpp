#include "../include/neuron.h"
#include "../include/activation_function.h"

#include <iostream>
#include <vector>
#include <random>

using namespace std;

Neuron::Neuron(int weights_size)
{
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(0.0, 1.0);

    activation_function = new ActivationFunction(ActivationFunction::ReLU);

    weights = vector<double>(weights_size);
    for (int i = 0; i < weights_size; i++)
    {
        weights[i] = distribution(gen);
    }

    this->bias = distribution(gen);
}

Neuron::~Neuron()
{
}

double Neuron::merge_input(vector<double> inputs)
{
    double total = 0;
    for (size_t i = 0; i < inputs.size(); i++)
    {
        total += inputs[i] * weights[i];
    }
    return total + bias;
}

double Neuron::feed_forward(vector<double> inputs)
{
    return activation_function->compute(merge_input(inputs));
}

// return [i->wij*error of the neuron j]
vector<double> Neuron::feed_backward(vector<double> input, double output, double error, double learning_rate)
{
    vector<double> backward_errors = vector<double>(input.size());
    for (size_t i = 0; i < input.size(); i++)
    {
        backward_errors[i] = weights[i] * error;
        weights[i] -= learning_rate * error * input[i];
    }

    return backward_errors;
}
