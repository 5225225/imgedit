#include <stdio.h>
#include <math.h>
#include <stdlib.h>


#include "imgedit.h"
#include "filters.h"

void BoxBlur(image *img, uint32_t xsize, uint32_t ysize) {
    image *origimg = CloneImage(img);
    for (int64_t y=0; y<img->height; y++) {
        for (int64_t x=0; x<img->width; x++) {
            pixel p = {0};
            uint64_t valid = 0;
            for (int64_t xdiff=0;xdiff<=xsize;xdiff++) {
                for (int64_t ydiff=0;ydiff<=ysize;ydiff++) {
                    if (PixelInBounds(origimg, x + xdiff, y + ydiff)) {
                        pixel newp = GetPixel(origimg, x + xdiff, y + ydiff);
                        p.r += (newp.r);
                        p.g += (newp.g);
                        p.b += (newp.b);
                        p.a += (newp.a);
                        valid++;
                    }
                }
            }
            p.r /= (double) valid;
            p.g /= (double) valid;
            p.b /= (double) valid;
            p.a /= (double) valid;
            SetPixel(img, x, y, p);
        }
    }
    FreeImage(origimg);
}

void HorizontalBoxBlur(image *img, uint32_t size) {
    image *origimg = CloneImage(img);
    for (int64_t y=0; y<img->height; y++) {
        for (int64_t x=0; x<img->width; x++) {
            pixel p = {0};
            uint64_t valid = 0;
            for (int64_t xdiff=0-(int64_t)size;xdiff<=size;xdiff++) {
                if (PixelInBounds(origimg, x + xdiff, y)) {
                    pixel newp = GetPixel(origimg, x + xdiff, y);
                    p.r += (newp.r);
                    p.g += (newp.g);
                    p.b += (newp.b);
                    p.a += (newp.a);
                    valid++;
                }
            }
            p.r /= (double) valid;
            p.g /= (double) valid;
            p.b /= (double) valid;
            p.a /= (double) valid;
            SetPixel(img, x, y, p);
        }
    }
    FreeImage(origimg);
}

void VerticalBoxBlur(image *img, uint32_t size) {
    image *origimg = CloneImage(img);
    for (int64_t y=0; y<img->height; y++) {
        for (int64_t x=0; x<img->width; x++) {
            pixel p = {0};
            uint64_t valid = 0;
            for (int64_t ydiff=0-(int64_t)size;ydiff<=size;ydiff++) {
                if (PixelInBounds(origimg, x, y + ydiff)) {
                    pixel newp = GetPixel(origimg, x, y + ydiff);
                    p.r += (newp.r);
                    p.g += (newp.g);
                    p.b += (newp.b);
                    p.a += (newp.a);
                    valid++;
                }
            }
            p.r /= (double) valid;
            p.g /= (double) valid;
            p.b /= (double) valid;
            p.a /= (double) valid;
            SetPixel(img, x, y, p);
        }
    }
    FreeImage(origimg);
}

void FakeGaussianBlur(image *img, double sx, double sy) {
    uint32_t dx = (uint32_t) (sx * 3*sqrt(2*M_PI)/4 + 0.5) / 2;
    uint32_t dy = (uint32_t) (sy * 3*sqrt(2*M_PI)/4 + 0.5) / 2;
    for (int i=0; i<3; i++) {
        HorizontalBoxBlur(img, dx);
        VerticalBoxBlur(img, dy);
    }
}

void FillPixel(image *img, pixel pixel) {
    for(uint64_t i=0; i<(img->width)*(img->height); i++) {
        SetRawPixel(img, i, pixel);
    }
}

void WhiteNoise(image *img) {
    for(uint64_t i=0; i<(img->width)*(img->height); i++) {
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wbad-function-cast"
        double brightness = ((double)rand()/(double)(RAND_MAX));
        #pragma clang diagnostic pop
        SetRawPixel(img, i, (pixel) {brightness, brightness, brightness, 1});
    }
}

void SubtractRGB(image *a, image *b) {
    for(uint64_t i=0; i<(a->width)*(a->height); i++) {
        pixel apixel = GetRawPixel(a, i);
        pixel bpixel = GetRawPixel(b, i);

        pixel result = {
            apixel.r - bpixel.r,
            apixel.g - bpixel.g,
            apixel.b - bpixel.b,
            apixel.a
        };
        SetRawPixel(a, i, result);
    }
}
