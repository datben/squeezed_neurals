#include <vector>

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

    double feed_forward(vector<double> inputs);

    double compute_error(vector<double> backwards_errors, double current_output);

    vector<double> feed_backward(vector<double> inputs, double output, double error, double learning_rate);
};

#endif