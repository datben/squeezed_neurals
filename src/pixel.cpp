#include "../include/pixel.h"
#include "../include/neural_network.h"
#include <stdlib.h>
#include <vector>

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
    d.inputs.reserve(height * width);
    d.expected_outputs.reserve(height * width);
    d.nb_data_points = height * width;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Pixel p = get_pixel(image, width, x, y, channels);
            d.inputs[x * width + y] = {(double)x / width, (double)y / height};
            d.expected_outputs[x * width + y] = {(double)p.red / 255,
                                                 (double)p.green / 255,
                                                 (double)p.blue / 255};
        }
    }
    return d;
}

vector<unsigned char> create_image_from_neural_network(NeuralNetwork *nn, int width, int height)
{
    vector<unsigned char> img(height * width * 3 * sizeof(char));
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            vector<double> input(2);
            input[0] = x / width;
            input[1] = y / height;
            vector<double> output = nn->feed_forward_final_layer(input);
            img[y * width * 3 + x * 3] = output[0];
            img[y * width * 3 + x * 3 + 1] = output[1];
            img[y * width * 3 + x * 3 + 2] = output[2];
        }
    }
    return img;
}
