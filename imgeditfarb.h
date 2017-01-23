#include <stdio.h>
#define FARBFELD_MAGIC_STRING "farbfeld"

struct image *ReadImageFarbfeld(FILE *fp);
void WriteImageFarbfeld(struct image *img, FILE *fp);
