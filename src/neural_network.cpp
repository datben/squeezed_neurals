#include "../include/neural_network.h"
#include "../include/layer.h"

#include <iostream>

using namespace std;

NeuralNetwork::NeuralNetwork(int input_size, vector<int> layers_sizes)
{
    this->input_size = input_size;
    this->layers.reserve(layers_sizes.size());
    for (int i = 0; i < layers_sizes.size(); i++)
    {
        this->layers[i] = new Layer(input_size, layers_sizes[i]);
        input_size = layers_sizes[i];
    }
}

NeuralNetwork::~NeuralNetwork()
{
}

vector<double> NeuralNetwork::feed_forward_final_layer(vector<double> inputs)
{
    if (inputs.size() != this->input_size)
        throw invalid_argument("The number of inputs must be equal to the number of neurons in the input layer");

    vector<double> outputs = inputs;
    for (int i = 0; i < this->layers.size(); i++)
    {
        outputs = this->layers[i]->feed_forward(outputs);
    }
    return outputs;
}

vector<vector<double>> NeuralNetwork::feed_forward_layers(vector<double> inputs)
{
    if (inputs.size() != this->input_size)
        throw invalid_argument("The number of inputs must be equal to the number of neurons in the input layer");

    vector<vector<double>> outputs;
    outputs.reserve(this->layers.size());
    for (int i = 0; i < this->layers.size(); i++)
    {
        outputs[i] = this->layers[i]->feed_forward(inputs);
        inputs = outputs[i];
    }
    return outputs;
}

NeuralNetwork *NeuralNetwork::add_layer(int size)
{
    int input_size = this->input_size;
    if (this->layers.size() > 0)
        input_size = this->layers[this->layers.size() - 1]->get_nb_neurons();
    this->layers.push_back(new Layer(input_size, size));
    return this;
}

int NeuralNetwork::depth()
{
    return this->layers.size();
}

void NeuralNetwork::train_once(vector<double> inputs, vector<double> expected_outputs, double learning_rate)
{
    if (inputs.size() != this->input_size)
        throw invalid_argument("The number of inputs must be equal to the number of neurons in the input layer");

    vector<vector<double>> outputs = feed_forward_layers(inputs);
    vector<double> errors;
    errors.reserve(outputs.size());
    for (int i = 0; i < outputs.size(); i++)
    {
        errors[i] = expected_outputs[i] - outputs[depth() - 1][i];
    }

    for (int i = this->layers.size() - 1; i >= 0; i--)
    {
        vector<double> layer_inputs;
        if (i == 0)
            layer_inputs = inputs;
        else
            layer_inputs = outputs[i - 1];

        errors = this->layers[i]->train(layer_inputs, outputs[i], errors, learning_rate);
    }
}

void NeuralNetwork::train(vector<vector<double>> inputs, vector<vector<double>> expected_outputs, double learning_rate)
{
    if (inputs.size() != expected_outputs.size())
        throw invalid_argument("The number of inputs must be equal to the number of expected outputs");

    for (int i = 0; i < inputs.size(); i++)
    {
        train_once(inputs[i], expected_outputs[i], learning_rate);
    }
}