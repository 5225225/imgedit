void BoxBlur(image *img, uint32_t xsize, uint32_t ysize);
void FakeGaussianBlur(image *img, double sx, double sy);
void HorizontalBoxBlur(image *img, uint32_t size);
void VerticalBoxBlur(image *img, uint32_t size);

void FillPixel(image *img, pixel pixel);
void WhiteNoise(image *img);

void SubtractRGB(image *a, image *b);
