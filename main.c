#include "imgedit.h"
#include "imgeditfarb.h"
#include "imgeditppm.h"
#include "filters.h"

int main() {
    image *img = ReadImageFarbfeld(fopen("scrot.ff","r"));

    image *smallblur = CloneImage(img);
    image *largeblur = CloneImage(img);

    FakeGaussianBlur(smallblur, 3, 3);
    FakeGaussianBlur(largeblur, 6, 6);

    SubtractRGB(largeblur, smallblur);

    FillPixel(largeblur, (pixel){0.5, 0.5, 0.5, 1});

    WriteImageFarbfeld(largeblur, fopen("scrot2.ff","w"));
    FreeImage(img);
}
