#include <stdio.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <endian.h>

#include "imgedit.h"
#include "imgeditppm.h"
#include "util.c"

struct image *ReadImagePPM(FILE *fp) {
    char magic[3] = "  ";
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t maxval = 0;
    fread(magic, 2, 1, fp);
    if (strcmp(magic, "P6") != 0) {
        return NULL;
    }


    fscanf(fp, " %d %d %d", &width, &height, &maxval);

    if (!isspace(fgetc(fp))) {
        return NULL;
    }

    struct image *img = InitImage(width, height);

    size_t readsize = maxval < 256 ? 1 : 2;

    for (uint64_t i=0; i<width*height; i++) {
        uint16_t r;
        uint16_t g;
        uint16_t b;

        fread(&r, readsize, 1, fp);
        fread(&g, readsize, 1, fp);
        fread(&b, readsize, 1, fp);

        double newr = le16toh(r) / (double) maxval;
        double newg = le16toh(g) / (double) maxval;
        double newb = le16toh(b) / (double) maxval;

        SetRawPixel(img, i, (struct pixel){newr, newg, newb, 1.0});
    }

    return img;
}
