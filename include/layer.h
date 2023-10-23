#include <vector>
#include "neuron.h"

using namespace std;

#ifndef LAYER
#define LAYER

class Layer
{
private:
    /* data */
    vector<Neuron *> neurons;

public:
    Layer(int input_size, int nb_neurons);

    ~Layer();

    vector<double> feed_forward(vector<double> inputs);

    vector<double> train(vector<double> inputs, vector<double> outputs, vector<double> errors, double learning_rate);

    int get_nb_neurons();
};

#endif