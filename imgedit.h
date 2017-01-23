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
    struct pixel *pixels;
} image;

struct image *InitImage(uint32_t width, uint32_t height);
struct image *CloneImage(struct image *img);
struct image *SelectBox(struct image *img, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void CopyImage(struct image *baseimg, struct image *topimg, uint32_t x1, uint32_t y1);
void FreeImage(struct image *img);

struct pixel GetPixel(struct image *img, int64_t x, int64_t y);
struct pixel GetRawPixel(struct image *img, uint64_t i);

char PixelInBounds(struct image *img, int64_t x, int64_t y);

void SetPixel(struct image *img, int64_t x, int64_t y, struct pixel pixel);
void SetRawPixel(struct image *img, uint64_t i, struct pixel pixel);
