#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <errno.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"

char *args_shift(int *argc, char ***argv)
{
	assert(*argc > 0);
	char *result = **argv;
	(*argc) -= 1;
	(*argv) += 1;
	return result;
}

int main(int argc, char **argv)
{
	const char *program = args_shift(&argc, &argv);

	if (argc <= 0)
	{
		fprintf(stderr, "Usage: %s <image1> <image2>\n", program);
		fprintf(stderr, "ERROR: no image1 is provided\n");
		return 1;
	}
	const char *img1_file_path = args_shift(&argc, &argv);
}