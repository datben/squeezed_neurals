#include "../include/pixel.h"

Pixel get_pixel(unsigned char *img, int width, int x, int y)
{
    Pixel p;
    p.red = img[y * width + x];
    p.green = img[y * width + x + 1];
    p.blue = img[y * width + x + 2];
    return p;
}