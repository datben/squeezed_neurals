#include "../include/neural_network.h"

#ifndef PIXEL
#define PIXEL

typedef struct
{
    unsigned char red, green, blue;
} Pixel;

Pixel get_pixel(unsigned char *img, int width, int x, int y, int channels);

typedef struct
{
    double **inputs;
    double **expected_outputs;
    int nb_data_points;
} ImageTrainingData;

ImageTrainingData prepare_training_data_from_image(unsigned char *image, int width, int height, int channels);

unsigned char *create_image_from_neural_network(NeuralNetwork *nn, int width, int height);

#endif