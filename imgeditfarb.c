#include <stdio.h>
#include <stdint.h>
#include <endian.h>
#include <string.h>

#include "imgedit.h"
#include "imgeditfarb.h"
#include "util.c"

struct image *ReadImageFarbfeld(FILE *fp) {
    char magic[9] = "        ";
    uint32_t width = 0;
    uint32_t height = 0;
    fread(magic, 8, 1, fp);
    if (strcmp(magic, FARBFELD_MAGIC_STRING) != 0) {
        return NULL;
    }
    fread(&width, sizeof(width), 1, fp);
    fread(&height, sizeof(height), 1, fp);
    width = be32toh(width);
    height = be32toh(height);


    struct image *img = InitImage(width, height);

    for (uint64_t i=0; i<width*height; i++) {
        uint16_t r;
        uint16_t g;
        uint16_t b;
        uint16_t a;

        fread(&r, sizeof(r), 1, fp);
        fread(&g, sizeof(g), 1, fp);
        fread(&b, sizeof(b), 1, fp);
        fread(&a, sizeof(a), 1, fp);

        double newr = be16toh(r) / 65535.0;
        double newg = be16toh(g) / 65535.0;
        double newb = be16toh(b) / 65535.0;
        double newa = be16toh(a) / 65535.0;

        struct pixel pixel = {newr, newg, newb, newa};

        SetRawPixel(img, i, pixel);
    }

    return img;
}

void WriteImageFarbfeld(struct image *img, FILE *fp) {
    char magic[] = FARBFELD_MAGIC_STRING;
    uint32_t width = img -> width;
    uint32_t height = img -> height;

    uint32_t adjusted_width = htobe32(width);
    uint32_t adjusted_height = htobe32(height);

    fwrite(magic, 8, 1, fp);
    fwrite(&adjusted_width, sizeof(width), 1, fp);
    fwrite(&adjusted_height, sizeof(height), 1, fp);

    for (uint64_t i=0; i<width*height; i++) {
        struct pixel pixel = GetRawPixel(img, i);

        uint16_t r = htobe16(CLAMP(pixel.r * 65535, 0, 65535));
        uint16_t g = htobe16(CLAMP(pixel.g * 65535, 0, 65535));
        uint16_t b = htobe16(CLAMP(pixel.b * 65535, 0, 65535));
        uint16_t a = htobe16(CLAMP(pixel.a * 65535, 0, 65535));

        fwrite(&r, sizeof(r), 1, fp);
        fwrite(&g, sizeof(g), 1, fp);
        fwrite(&b, sizeof(b), 1, fp);
        fwrite(&a, sizeof(a), 1, fp);
    }
}
