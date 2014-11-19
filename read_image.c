#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_image.h"

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
