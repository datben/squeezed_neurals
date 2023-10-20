#ifndef ACTIVATION_FN_H
#define ACTIVATION_FN_H

class ActivationFunction
{
public:
    enum Value : char
    {
        SIGMOID,
        ReLU,
    };

    ActivationFunction(Value value);
    ~ActivationFunction();

    double compute(double x);

    double derivative(double x);

private:
    Value value;
};

#endif