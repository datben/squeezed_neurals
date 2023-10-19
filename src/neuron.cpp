#include "../include/neuron.h"

#include <iostream>
#include <vector>
#include <random>

using namespace std;

Neuron::Neuron(int weights_size)

{
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(0.0, 1.0);

    weights.reserve(weights_size);
    for (int i = 0; i < weights_size; i++)
    {
        weights[i] = distribution(gen);
    }

    this->bias = distribution(gen);
}

Neuron::~Neuron()
{
}

double Neuron::feed_forward(vector<double> inputs)
{
    double total = 0;
    for (size_t i = 0; i < inputs.size(); i++)
    {
        total += inputs[i] * weights[i];
    }
    return total + bias;
}

// return [i->wij*error of the neuron j]
vector<double> Neuron::feed_backward(vector<double> input, double output, double error, double learning_rate)
{
    vector<double> backward_errors;
    backward_errors.reserve(input.size());
    for (size_t i = 0; i < input.size(); i++)
    {
        backward_errors[i] = weights[i] * error;
        weights[i] -= learning_rate * error * output;
    }
    return backward_errors;
}
