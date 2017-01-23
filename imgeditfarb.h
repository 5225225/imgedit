#include <stdio.h>
#define FARBFELD_MAGIC_STRING "farbfeld"

image *ReadImageFarbfeld(FILE *fp);
void WriteImageFarbfeld(image *img, FILE *fp);
