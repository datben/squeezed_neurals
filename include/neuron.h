#include <vector>
#include "activation_function.h"

using namespace std;

#ifndef NEURON
#define NEURON

class Neuron
{
private:
    /* data */
    vector<double> weights;
    double bias;

public:
    Neuron(int nb_weights);
    ~Neuron();
    ActivationFunction *activation_function;

    double feed_forward(vector<double> inputs);
    double merge_input(vector<double> inputs);

    double compute_error(vector<double> backwards_errors, double current_output);

    vector<double> feed_backward(vector<double> inputs, double output, double error, double learning_rate);
};

#endif