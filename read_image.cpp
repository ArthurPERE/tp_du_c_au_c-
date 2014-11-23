#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_image.h"

read_image::read_image(void)
{
  old_width=0;
  old_height=0;
  old_data=0;
}


//---------------------------------------------------
//Getteur
//---------------------------------------------------
int read_image::Get_old_width(void) const
{
	return old_width;
}
int read_image::Get_old_height(void) const
{
	return old_height;
}
u_char* read_image::Get_old_data(void) const
{
	return old_data;
}

//---------------------------------------------------
//other function
//---------------------------------------------------

void read_image::ppm_read_from_file(const char *name)
{
	//open the file
	FILE *file=fopen(name,"rb");
	int width,height;
	
	// Read file header
	fscanf(file, "P6\n%d %d\n255\n", &width, &height);
	
	// Allocate memory according to width and height
	u_char *data = (u_char*) malloc(3 * width * height * sizeof(u_char));
	
	// Read the actual image data
	fread(data, 3, width * height, file);
	
	//refresh the private variable
	old_width = width;
	old_height = height;
	old_data = data;
	
	//close the file
	fclose(file);
}

//---------------------------------------------------
//destructeur
//---------------------------------------------------

void read_image::clear(void)
{
	delete old_data;
}
