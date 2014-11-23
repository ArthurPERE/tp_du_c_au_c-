class modification_and_write_image
{
private:
	int new_width1;
	int new_height1;
	u_char *new_data1;

public:
	modification_and_write_image(void);
	//Getteurs

	int Get_new_width(void) const;
	int Get_new_height(void) const;
	u_char* Get_new_data(void) const;
	
	// other fuction
	// Desaturate (transform to B&W) <image> (of size <width> * <height>)
	void ppm_desaturate(u_char* image, int width, int height);
	
	// Shrink image (of original size <width> * <height>) by factor <factor>
	// <width> and <height> are updated accordingly
	void ppm_shrink(u_char** image, int& width, int& height, int factor);
	
	// Read the image contained in plain RGB ppm file <file>
	// into <data> and set <width> and <height> accordingly
	// Warning: data is malloc_ed, don't forget to free it
	void ppm_write_to_file(const char *name);

	//destructeur
	void clear(void);
};