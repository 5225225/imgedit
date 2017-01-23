#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#include "imgedit.h"
#include "util.c"

struct image *InitImage(uint32_t width, uint32_t height) {
    struct image *img = malloc(sizeof(struct image));
    img -> width = width;
    img -> height = height;
    img -> pixels = calloc(width*height, sizeof(struct pixel));
    return img;
}

struct image *CloneImage(struct image *origimg) {
    struct image *newimg = InitImage(origimg -> width, origimg -> height);
    for (uint64_t i=0; i<(newimg -> width)*(newimg->height); i++) {
        SetRawPixel(newimg, i, GetRawPixel(origimg, i));
    }
    return newimg;
}

struct image *SelectBox(struct image *img, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
    uint32_t width, height;
    width = x2 - x1;
    height = y2 - y1;
    struct image *newimg = InitImage(width, height);

    for (int64_t x=0; x<width; x++) {
        for (int64_t y=0; y<height; y++) {
            SetPixel(newimg, x, y, GetPixel(img, x1 + x, y1 + y));
        }
    }
    return newimg;
}

void CopyImage(struct image *baseimg, struct image *topimg, uint32_t x1, uint32_t y1) {
    uint32_t width, height;
    width = topimg -> width;
    height = topimg -> height;

    for (int64_t x=0; x<width; x++) {
        for (int64_t y=0; y<height; y++) {
            SetPixel(baseimg, x + x1, y + y1, GetPixel(topimg, x, y));
        }
    }
}


void FreeImage(struct image *img) {
    free(img -> pixels);
    free(img);
}

struct pixel GetPixel(struct image *img, int64_t x, int64_t y) {
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wshorten-64-to-32"
    uint32_t cx = CLAMP(x, 0, (img -> width)-1);
    uint32_t cy = CLAMP(y, 0, (img -> height)-1);
    #pragma clang diagnostic pop
    return GetRawPixel(img, cy*(img -> width)+cx);
}

struct pixel GetRawPixel(struct image *img, uint64_t i) {
    return img -> pixels[i];
}

char PixelInBounds(struct image *img, int64_t x, int64_t y) {
    uint32_t width = img -> width;
    uint32_t height = img -> height;
    return (x > 0) && (x < width) && (y > 0) && (y < height);
}

void SetPixel(struct image *img, int64_t x, int64_t y, struct pixel pixel) {
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wshorten-64-to-32"
    uint32_t cx = CLAMP(x, 0, (img -> width)-1);
    uint32_t cy = CLAMP(y, 0, (img -> height)-1);
    #pragma clang diagnostic pop
    SetRawPixel(img, cy*(img -> width)+cx, pixel);
}

void SetRawPixel(struct image *img, uint64_t i, struct pixel pixel) {
    img -> pixels[i] = pixel;
}
