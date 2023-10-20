
#include <vector>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"

#include "../include/neural_network.h"
#include "../include/pixel.h"

#define PIXEL_CHANNELS 3

char *args_shift(int *argc, char ***argv)
{
	assert(*argc > 0);
	char *result = **argv;
	(*argc) -= 1;
	(*argv) += 1;
	return result;
}

int write_image(char *filename, int width, int height, void *data)
{
	return stbi_write_png(filename, width, height, PIXEL_CHANNELS, data, width * PIXEL_CHANNELS);
}

int main(int argc, char **argv)
{

	char *program = args_shift(&argc, &argv);

	if (argc < 1)
	{
		fprintf(stderr, "Usage: %s <image>\n", program);
		fprintf(stderr, "ERROR: image is not provided\n");
		return 1;
	}
	char *img1_file_path = args_shift(&argc, &argv);

	int width, height, channels;
	unsigned char *data = stbi_load(img1_file_path, &width, &height, &channels, 3);

	if (data == NULL || channels < PIXEL_CHANNELS)
	{
		fprintf(stderr, "ERROR: image1 unsupported format\n");
		return 1;
	}

	NeuralNetwork nn(2, {10, 10, 3});

	ImageTrainingData train = prepare_training_data_from_image(data, width, height, channels);

	nn.train(train.inputs, train.expected_outputs, 0.1, 1);

	// out = create_image_from_neural_network(nn, width, height);

	// write_result = write_image("target/out-2.png", width, height, out);

	// if (!write_result)
	// {
	// 	fprintf(stderr, "ERROR: Could not write image\n");
	// 	return 1;
	// }

	// stbi_image_free(data);
	// stbi_image_free(out);

	return 0;
}