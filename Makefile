all: ppm.out

ppm.out: ppm.c modification_and_write_image.o read_image.o
	gcc -o ppm.out ppm.c modification_and_write_image.o read_image.o

modification_image.o: modification_and_write_image.c modification_and_write_image.h
	gcc -o modification_and_write_image.o modification_and_write_image.c -c

write_and_read_image.o: read_image.c read_image.h
	gcc -o read_image.o read_image.c -c
