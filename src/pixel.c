#include "../include/pixel.h"
#include "../include/neural_network.h"
#include <stdlib.h>

Pixel get_pixel(unsigned char *img, int width, int x, int y, int channels)
{
    Pixel p;
    p.red = img[(y * width + x) * channels];
    p.green = img[(y * width + x) * channels + 1];
    p.blue = img[(y * width + x) * channels + 2];
    return p;
}

ImageTrainingData prepare_training_data_from_image(unsigned char *image, int width, int height, int channels)
{
    ImageTrainingData d;
    d.inputs = (double **)malloc(height * width * sizeof(double *));
    d.expected_outputs = (double **)malloc(height * width * sizeof(double *));
    d.nb_data_points = height * width;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Pixel p = get_pixel(image, width, x, y, channels);
            d.inputs[x * width + y] = (double *)malloc(2 * sizeof(double));
            d.expected_outputs[x * width + y] = (double *)malloc(3 * sizeof(double));
            d.inputs[x * width + y][0] = x / width;
            d.inputs[x * width + y][1] = y / height;
            d.expected_outputs[x * width + y][0] = p.red / 255.0;
            d.expected_outputs[x * width + y][1] = p.green / 255.0;
            d.expected_outputs[x * width + y][2] = p.blue / 255.0;
        }
    }
    return d;
}

unsigned char *create_image_from_neural_network(const NeuralNetwork *nn, int width, int height)
{
    unsigned char *img = (unsigned char *)malloc(height * width * 3 * sizeof(char));
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double *input = (double *)malloc(2 * sizeof(double));
            input[0] = x / width;
            input[1] = y / height;
            double *output = compute_neural_network_output(nn, input);
            img[y * width * 3, x * 3] = output[0];
            img[y * width * 3, x * 3 + 1] = output[1];
            img[y * width * 3, x * 3 + 2] = output[2];
            free(output);
            free(input);
        }
    }
    return img;
}
