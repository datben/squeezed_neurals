#include "../include/neural_network.h"
#include <vector>

#ifndef PIXEL
#define PIXEL

typedef struct
{
    unsigned char red, green, blue;
} Pixel;

Pixel get_pixel(unsigned char *img, int width, int x, int y, int channels);

typedef struct
{
    vector<vector<double>> inputs;
    vector<vector<double>> expected_outputs;
    int nb_data_points;
} ImageTrainingData;

ImageTrainingData prepare_training_data_from_image(unsigned char *image, int width, int height, int channels);

vector<unsigned char> create_image_from_neural_network(NeuralNetwork *nn, int width, int height);

#endif