#ifndef write_and_read_image
#define write_and_read_image

//struct for old image
typedef struct
{
  int width;
  int height;
  u_char *data;
}old;

// Read the image contained in plain RGB ppm file <file>
// into <data> and set <width> and <height> accordingly
// Warning: data is malloc_ed, don't forget to free it
old* ppm_read_from_file(char *name);


#endif
