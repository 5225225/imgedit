void BoxBlur(struct image *img, uint32_t xsize, uint32_t ysize);
void FakeGaussianBlur(struct image *img, double sx, double sy);
void HorizontalBoxBlur(struct image *img, uint32_t size);
void VerticalBoxBlur(struct image *img, uint32_t size);

void FillPixel(struct image *img, struct pixel pixel);
void WhiteNoise(struct image *img);

void SubtractRGB(struct image *a, struct image *b);
