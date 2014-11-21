
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_image.h"
#include "modification_and_write_image.h"


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
  u_char* image_bw = new u_char[3 * width * height];
  memcpy(image_bw, image, 3 * width * height * sizeof(*image_bw));

  // Desaturate image_bw
  newimg* newimage = ppm_desaturate(image_bw, width, height);


  // Write the desaturated image into "gargouille_BW.ppm"
  ppm_write_to_file(newimage, "gargouille_BW.ppm");
  // Free the desaturated image


  //--------------------------------------------------------------------------
  // Create a resized copy of the image and
  // write it into "gargouille_small.ppm"
  //--------------------------------------------------------------------------
  // Copy image into image_small
  int width_small  = width;
  int height_small = height;
  u_char* image_small =new u_char[3 * width_small * height_small];
  memcpy(image_small, image, 3 * width_small * height_small * sizeof(*image_small));

  // Shrink image_small size 2-fold
  newimg * newimage1=ppm_shrink(&image_small, &width_small, &height_small, 2);

  // Write the desaturated image into "gargouille_small.ppm"
  ppm_write_to_file(newimage1, "gargouille_small.ppm");

  // Free the not yet freed images
  delete(oldimage->data);
  delete(oldimage);
  delete(newimage->data);
  delete(newimage);
  delete(newimage1->data);
  delete(newimage1);
  delete(image_small);

  return 0;
 
}
