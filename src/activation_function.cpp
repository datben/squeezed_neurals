#include "../include/activation_function.h"

#include <iostream>
#include <vector>
#include <random>

using namespace std;

ActivationFunction::ActivationFunction(Value value)
{
    this->value = value;
}

double ActivationFunction::compute(double x)
{
    switch (this->value)
    {
    case SIGMOID:
        return 1 / (1 + exp(-x));
    case ReLU:
        return max(0.0, x);
    case IDENTITY:
        return x;
    default:
        throw invalid_argument("Activation function not implemented");
    }
}

double ActivationFunction::derivative(double x)
{
    switch (this->value)
    {
    case SIGMOID:
        return x * (1 - x);
    case ReLU:
        return x > 0 ? 1 : 0;
    case IDENTITY:
        return 1;
    default:
        throw invalid_argument("Activation function not implemented");
    }
}

ActivationFunction::~ActivationFunction()
{
}