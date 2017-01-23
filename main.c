#include "imgedit.h"
#include "imgeditfarb.h"
#include "imgeditppm.h"
#include "filters.h"

int main() {
    struct image *img = ReadImageFarbfeld(fopen("scrot.ff","r"));

    struct image *smallblur = CloneImage(img);
    struct image *largeblur = CloneImage(img);

    FakeGaussianBlur(smallblur, 3, 3);
    FakeGaussianBlur(largeblur, 6, 6);

    SubtractRGB(largeblur, smallblur);

    FillPixel(largeblur, (struct pixel){0.5, 0.5, 0.5, 1});

    WriteImageFarbfeld(largeblur, fopen("scrot2.ff","w"));
    FreeImage(img);
}
