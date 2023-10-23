
#include <vector>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"

#include "../include/neural_network.h"
#include "../include/pixel.h"

char *args_shift(int *argc, char ***argv)
{
	assert(*argc > 0);
	char *result = **argv;
	(*argc) -= 1;
	(*argv) += 1;
	return result;
}

int write_image(char *filename, int width, int height, void *data, int channels)
{
	return stbi_write_png(filename, width, height, channels, data, width * channels);
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

	data = to_gray_scala(data, width, height, channels).data();

	// if (data == NULL)
	// {
	// 	fprintf(stderr, "ERROR: image1 unsupported format\n");
	// 	return 1;
	// }

	// printf("channel: %d\n", channels);
	// printf("width: %d\n", width);
	// printf("height: %d\n", height);

	// NeuralNetwork nn(2, {30, 10, 1});

	// ImageTrainingData train = prepare_training_data_from_color_image(data, width, height, channels);

	// nn.train(train.inputs, train.expected_outputs, 1E-6, 3000);

	// unsigned char *out = create_color_image_from_neural_network(&nn, width, height).data();

	int write_result = write_image((char *)"target/out-2.png", width, height, data, 1);

	if (!write_result)
	{
		fprintf(stderr, "ERROR: Could not write image\n");
		return 1;
	}

	return 0;
}