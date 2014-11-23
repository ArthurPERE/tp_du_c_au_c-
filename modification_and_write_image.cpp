#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modification_and_write_image.h"


modification_and_write_image::modification_and_write_image(void)
{
  new_width1=0;
  new_height1=0;
  new_data1=0;
}

//---------------------------------------------------
//Getteurs
//---------------------------------------------------

int modification_and_write_image::Get_new_width(void) const
{
	return new_width1;
}
int modification_and_write_image::Get_new_height(void) const
{
	return new_height1;
}
u_char* modification_and_write_image::Get_new_data(void) const
{
	return new_data1;
}

//---------------------------------------------------
//other function
//---------------------------------------------------

void modification_and_write_image::ppm_desaturate(u_char* image, int width, int height)
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

	//refresh the private variable
	new_width1 = width;
	new_height1 = height;
	new_data1 = image;
	
}

void modification_and_write_image:: ppm_shrink(u_char** image, int& width, int& height, int factor)
{
	// Compute new image size and allocate memory for the new image
	int new_width = (width) / factor;
	int new_height = (height) / factor;
	u_char* new_image = new u_char[3 * new_width * new_height];

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
			u_int red = 0;
			u_int green = 0;
			u_int blue = 0;
			// Compute coordinates and index of the first (top-left) pixel from the
			// model image corresponding to the pixel we are creating
			int x0 = x * factor;
			int y0 = y * factor;
			int i0 = 3 * (y0 * width + x0);
			// Compute RGB values for the new pixel
			int dx, dy;
			for (dx = 0 ; dx < factor ; dx++)
			{
				for (dy = 0 ; dy < factor ; dy++)
				{
					// Compute the offset of the current pixel (in the model image)
					// with regard to the top-left pixel of the current "set of pixels"
					int delta_i = 3 * (dy * width + dx);
					// Accumulate RGB values
					red += (*image)[i0+delta_i];
					green += (*image)[i0+delta_i+1];
					blue += (*image)[i0+delta_i+2];
				}
			}
			// Divide RGB values to get the mean values
			red /= factor_squared;
			green /= factor_squared;
			blue /= factor_squared;
			// Set new pixel's RGB values
			new_image[ 3 * (y * new_width + x) ] = red;
			new_image[ 3 * (y * new_width + x) + 1 ] = green;
			new_image[ 3 * (y * new_width + x) + 2 ] = blue;
		}
	}
	//refresh the private variable
        new_width1 = new_width;
	new_height1 = new_height;
	new_data1 = new_image;

}

void modification_and_write_image::ppm_write_to_file(const char *name)
{
	//open the file
	FILE *file=fopen(name,"wb");
	
	// Write header
	fprintf(file, "P6\n%d %d\n255\n", new_width1, new_height1);

	// Write pixels
	fwrite(new_data1, 3, new_width1*new_height1, file);

	//close the file
	fclose(file);
}

//-------------------------------------------------------------
//destructeur
//-------------------------------------------------------------
void modification_and_write_image::clear(void)
{
	delete new_data1;
}
