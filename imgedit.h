#include <stdint.h>

typedef struct {
    double r;
    double g;
    double b;
    double a;
} pixel;

typedef struct {
    uint32_t width;
    uint32_t height;
    pixel *pixels;
} image;

image *InitImage(uint32_t width, uint32_t height);
image *CloneImage(image *img);
image *SelectBox(image *img, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void CopyImage(image *baseimg, image *topimg, uint32_t x1, uint32_t y1);
void FreeImage(image *img);

pixel GetPixel(image *img, int64_t x, int64_t y);
pixel GetRawPixel(image *img, uint64_t i);

char PixelInBounds(image *img, int64_t x, int64_t y);

void SetPixel(image *img, int64_t x, int64_t y, pixel pixel);
void SetRawPixel(image *img, uint64_t i, pixel pixel);
