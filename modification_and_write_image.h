#ifndef modification_and_write_image
#define modification_and_write_image


//struct for the new image
typedef struct
{
  int width;
  int height;
  u_char *data;
}newimg;

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
newimg* ppm_desaturate(u_char* image, int width, int height);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
newimg* ppm_shrink(u_char** image, int *width, int *height, int factor);


#endif
