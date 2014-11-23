class read_image
{
private:
	int old_width;
	int old_height;
	u_char *old_data;
public:
	read_image(void);
	// Read the image contained in plain RGB ppm file <file>
	// into <data> and set <width> and <height> accordingly
	// Warning: data is malloc_ed, don't forget to free it
	void ppm_read_from_file(const char *name);

	//getteur
	int Get_old_width(void) const;
	int Get_old_height(void) const;
	u_char* Get_old_data(void) const;

	//destructeur
	void clear(void);
};