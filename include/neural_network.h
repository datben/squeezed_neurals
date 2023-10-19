#include <vector>
#include "layer.h"

using namespace std;

#ifndef NEURAL_NETWORK
#define NEURAL_NETWORK

class NeuralNetwork
{
private:
    /* data */
    int input_size;
    vector<Layer *> layers;

public:
    NeuralNetwork(int input_size, vector<int> layers_sizes);
    ~NeuralNetwork();

    NeuralNetwork *add_layer(int size);

    vector<double> feed_forward_final_layer(vector<double> inputs);
    vector<vector<double>> feed_forward_layers(vector<double> inputs);

    void train_once(vector<double> inputs, vector<double> expected_outputs, double learning_rate);
    void train(vector<vector<double>> inputs, vector<vector<double>> expected_outputs, double learning_rate);

    int depth();
};

#endif