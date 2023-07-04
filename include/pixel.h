#ifndef PIXEL
#define PIXEL

typedef struct
{
    unsigned char red, green, blue;
} Pixel;

Pixel get_pixel(unsigned char *img, int width, int x, int y);

#endif