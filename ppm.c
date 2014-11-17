
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



//============================================================================
//                           Function declarations
//============================================================================
//struct for the new image
typedef struct
{
  int width1;
  int height1;
  u_char *data;
}new;

//struct for old image
typedef struct
{
  int width;
  int height;
  u_char *data;
}old;

// Write the image contained in <data> (of size <width> * <height>)
// into plain RGB ppm file <file>
void ppm_write_to_file(int width, int height, u_char* data, char *name);

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
old* ppm_read_from_file(char *name);

// Desaturate (transform to B&W) <image> (of size <width> * <height>)
void ppm_desaturate(u_char* image, int width, int height);

// Shrink image (of original size <width> * <height>) by factor <factor>
// <width> and <height> are updated accordingly
void ppm_shrink(u_char** image, int *width, int *height, int factor);




//============================================================================
//                                  Main
//============================================================================
int main(int argc, char* argv[])
{

  //--------------------------------------------------------------------------
  // Read file "gargouille.ppm" into image (width and height)
  //--------------------------------------------------------------------------
  old *oldimage = ppm_read_from_file("gargouille.ppm");
  int width=oldimage->width;
  int height=oldimage->height;
  u_char *image=oldimage->data;

  //--------------------------------------------------------------------------
  // Create a desaturated (B&W) copy of the image we've just read and
  // write it into "gargouille_BW.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_bw
  int width_bw  = width;
  int height_bw = height;
  u_char* image_bw = (u_char*) malloc(3 * width * height * sizeof(*image_bw));
  memcpy(image_bw, image, 3 * width * height * sizeof(*image_bw));

  // Desaturate image_bw
  ppm_desaturate(image_bw, width, height);

  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(width, height, image_bw, "gargouille_BW.ppm");

  // Free the desaturated image
  free(image_bw);


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  int width_small  = width;
  int height_small = height;
  u_char* image_small = (u_char*) malloc(3 * width_small * height_small * sizeof(*image_small));
  memcpy(image_small, image, 3 * width_small * height_small * sizeof(*image_small));

  // Shrink image_small size 2-fold
  ppm_shrink(&image_small, &width_small, &height_small, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(width_small, height_small, image_small, "gargouille_small.ppm");

  // Free the not yet freed images
  free(oldimage->data);
  free(image_small);
  free(oldimage);
  return 0;
}



//============================================================================
//                           Function declarations
//============================================================================
void ppm_write_to_file(int width, int height, u_char* data, char *name)
{
  //open the file
  FILE *file=fopen(name,"wb");

  // Write header
  fprintf(file, "P6\n%d %d\n255\n", width, height);

  // Write pixels
  fwrite(data, 3, width*height, file);
  
  //close the file
  fclose(file);
}

old* ppm_read_from_file(char *name)
{
  //open the file
  FILE  *file=fopen(name,"rb");
  int width,height;
  
   //allocate memory for the structure for the old image
  old * oldimage=(old*)malloc(sizeof(old));

  // Read file header
  fscanf(file, "P6\n%d %d\n255\n", &width, &height);

  // Allocate memory according to width and height
  u_char *data = (u_char*) malloc(3 * width * height * sizeof(u_char));

  // Read the actual image data
  fread(data, 3, width * height, file);
  oldimage->width=width;
  oldimage->height=height;
  oldimage->data=data;

  //close the file
  fclose(file);

  return oldimage;

}

void ppm_desaturate(u_char* image, int width, int height)
{
  int x, y;

  // For each pixel ...
  for (x = 0 ; x < width ; x++)
  {
    for (y = 0 ; y < height ; y++)
    {
      u_int grey_lvl = 0;
      int rgb_canal;

      // Compute the grey level
      for (rgb_canal = 0 ; rgb_canal < 3 ; rgb_canal++)
      {
        grey_lvl += image[ 3 * (y * width + x) + rgb_canal ];
      }
      grey_lvl /= 3;
      assert(grey_lvl >= 0 && grey_lvl <=255);

      // Set the corresponding pixel's value in new_image
      memset(&image[3 * (y * width + x)], grey_lvl, 3);
    }
  }
}

void ppm_shrink(u_char** image, int *width, int *height, int factor)
{
  // Compute new image size and allocate memory for the new image
  int new_width   = (*width) / factor;
  int new_height  = (*height) / factor;
  u_char* new_image = (u_char*) malloc(3 * new_width * new_height * sizeof(*new_image));

  // Precompute factor^2 (for performance reasons)
  int factor_squared = factor * factor;

  // For each pixel of the new image...
  int x, y;
  for (x = 0 ; x < new_width ; x++)
  {
    for (y = 0 ; y < new_height ; y++)
    {
      // ... compute the average RGB values of the set of pixels (a square of side factor)
      // that correspond to the pixel we are creating.

      // Initialize RGB values for the new image's pixel
      u_int red   = 0;
      u_int green = 0;
      u_int blue  = 0;

      // Compute coordinates and index of the first (top-left) pixel from the
      // model image corresponding to the pixel we are creating
      int x0 = x * factor;
      int y0 = y * factor;
      int i0 = 3 * (y0 * (*width) + x0);

      // Compute RGB values for the new pixel
      int dx, dy;
      for (dx = 0 ; dx < factor ; dx++)
      {
        for (dy = 0 ; dy < factor ; dy++)
        {
          // Compute the offset of the current pixel (in the model image)
          // with regard to the top-left pixel of the current "set of pixels"
          int delta_i = 3 * (dy * (*width) + dx);

          // Accumulate RGB values
          red   += (*image)[i0+delta_i];
          green += (*image)[i0+delta_i+1];
          blue  += (*image)[i0+delta_i+2];
        }
      }

      // Divide RGB values to get the mean values
      red   /= factor_squared;
      green /= factor_squared;
      blue  /= factor_squared;

      // Set new pixel's RGB values
      new_image[ 3 * (y * new_width + x) ]     = red;
      new_image[ 3 * (y * new_width + x) + 1 ] = green;
      new_image[ 3 * (y * new_width + x) + 2 ] = blue;
    }
  }

  // Update image size
  *width  = new_width;
  *height = new_height;

  // Update image
  free(*image);
  *image = new_image;
}



































