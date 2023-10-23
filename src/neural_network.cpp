#include "../include/neural_network.h"
#include "../include/layer.h"

#include <iostream>
#include <vector>
#include <random>

using namespace std;

NeuralNetwork::NeuralNetwork(size_t input_size, vector<int> layers_sizes)
{
    this->input_size = input_size;
    for (size_t i = 0; i < layers_sizes.size(); i++)
    {
        this->add_layer(layers_sizes[i]);
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
    for (size_t i = 0; i < this->layers.size(); i++)
    {
        outputs = this->layers[i]->feed_forward(outputs);
    }
    return outputs;
}

vector<vector<double>> NeuralNetwork::feed_forward_layers(vector<double> inputs)
{
    if (inputs.size() != this->input_size)
        throw invalid_argument("The number of inputs must be equal to the number of neurons in the input layer");

    vector<vector<double>> outputs = vector<vector<double>>(this->layers.size());
    for (size_t i = 0; i < this->layers.size(); i++)
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

double norm_vec(vector<double> vec)
{
    double sum = 0;
    for (size_t i = 0; i < vec.size(); i++)
    {
        sum += vec[i] * vec[i];
    }
    return sqrt(sum);
}

double NeuralNetwork::train_once(vector<double> inputs, vector<double> expected_outputs, double learning_rate)
{
    if (inputs.size() != this->input_size)
        throw invalid_argument("The number of inputs must be equal to the number of neurons in the input layer");

    vector<vector<double>> outputs = feed_forward_layers(inputs);
    vector<double> errors = vector<double>(expected_outputs.size());
    for (size_t i = 0; i < expected_outputs.size(); i++)
    {
        errors[i] = expected_outputs[i] - outputs[depth() - 1][i];
    }

    double err = norm_vec(errors) / 2;

    for (int i = this->layers.size() - 1; i >= 0; i--)
    {
        vector<double> layer_inputs;
        if (i == 0)
            layer_inputs = inputs;
        else
            layer_inputs = outputs[i - 1];

        errors = this->layers[i]->train(layer_inputs, outputs[i], errors, learning_rate);
    }

    return err;
}

double NeuralNetwork::train(vector<vector<double>> inputs, vector<vector<double>> expected_outputs, double learning_rate, unsigned int repeat)
{
    if (inputs.size() != expected_outputs.size())
        throw invalid_argument("The number of inputs must be equal to the number of expected outputs");

    int n = 0;
    while (n < repeat)
    {

        double err_n = 0;
        for (size_t i = 0; i < inputs.size(); i++)
        {
            double err = train_once(inputs[i], expected_outputs[i], learning_rate);
            err_n += err;
        }

        if (n % 100 == 0)
        {
            printf("Epoch : %i\n", n);
            printf("Error : %f\n", err_n / inputs.size());
        }

        n++;
    }

    return 0;
}
