#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <errno.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"

#define PIXEL_CHANNELS 3

#include "../include/pixel.h"
#include "../include/neuron.h"
#include "../include/neural_network.h"
#include "../include/math_utils.h"

char *args_shift(int *argc, char ***argv)
{
	assert(*argc > 0);
	char *result = **argv;
	(*argc) -= 1;
	(*argv) += 1;
	return result;
}

int write_image(char const *filename, int width, int height, const void *data)
{
	return stbi_write_png(filename, width, height, PIXEL_CHANNELS, data, width * PIXEL_CHANNELS);
}

int main(int argc, char **argv)
{
	const char *program = args_shift(&argc, &argv);

	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <image1> <image2>\n", program);
		fprintf(stderr, "ERROR: no image1 or/and image2 are not provided\n");
		return 1;
	}
	const char *img1_file_path = args_shift(&argc, &argv);
	const char *img2_file_path = args_shift(&argc, &argv);

	int width, height, channels;
	unsigned char *data = stbi_load(img1_file_path, &width, &height, &channels, 0);

	if (data == NULL || channels != PIXEL_CHANNELS)
	{
		fprintf(stderr, "ERROR: image1 unsupported format\n");
		return 1;
	}

	int write_result = write_image(img2_file_path, width, height / 2, data);

	if (!write_result)
	{
		fprintf(stderr, "ERROR: Could not write image %s\n", img2_file_path);
		return 1;
	}

	init_rand();

	int layer_size[3] = {8, 8, 3};
	NeuralNetwork *nn = generate_random_neural_network(3, layer_size, 2);
	double inputs[3] = {1.0, 2.0, 3.0};

	double **out = compute_neural_network_output(nn, inputs);

	printf("%f\n", out[nn->nb_layer - 1][0]);

	stbi_image_free(data);

	return 0;
}