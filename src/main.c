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
		fprintf(stderr, "Usage: %s <image>\n", program);
		fprintf(stderr, "ERROR: image is not provided\n");
		return 1;
	}
	const char *img1_file_path = args_shift(&argc, &argv);

	int width, height, channels;
	unsigned char *data = stbi_load(img1_file_path, &width, &height, &channels, 3);

	if (data == NULL || channels < PIXEL_CHANNELS)
	{
		fprintf(stderr, "ERROR: image1 unsupported format\n");
		return 1;
	}

	init_rand();

	int layer_size[3] = {8, 8, 3};
	NeuralNetwork *nn = generate_random_neural_network(3, layer_size, 2);

	unsigned char *out = create_image_from_neural_network(nn, width, height);

	int write_result = write_image("target/out-1.png", width, height, out);

	if (!write_result)
	{
		fprintf(stderr, "ERROR: Could not write image\n");
		return 1;
	}

	ImageTrainingData img_data = prepare_training_data_from_image(data, width, height, channels);

	train_neural_network(nn, 0.001, 10000, img_data.nb_data_points, img_data.inputs, img_data.expected_outputs);

	out = create_image_from_neural_network(nn, width, height);

	write_result = write_image("target/out-2.png", width, height, out);

	if (!write_result)
	{
		fprintf(stderr, "ERROR: Could not write image\n");
		return 1;
	}

	stbi_image_free(data);
	stbi_image_free(out);

	return 0;
}