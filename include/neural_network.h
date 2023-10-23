#include <vector>
#include "layer.h"

using namespace std;

#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

class NeuralNetwork
{
private:
    /* data */
    size_t input_size;
    vector<Layer *> layers;

public:
    NeuralNetwork(size_t input_size, vector<int> layers_sizes);
    ~NeuralNetwork();

    NeuralNetwork *add_layer(int size);

    vector<double> feed_forward_final_layer(vector<double> inputs);
    vector<vector<double>> feed_forward_layers(vector<double> inputs);

    double train_once(vector<double> inputs, vector<double> expected_outputs, double learning_rate);
    double train(vector<vector<double>> inputs, vector<vector<double>> expected_outputs, double learning_rate, unsigned int repeat);

    int depth();
};

#endif