all: ppm.out

ppm.out: ppm.cpp modification_and_write_image.o read_image.o
	g++ -o ppm.out ppm.cpp modification_and_write_image.o read_image.o

modification_image.o: modification_and_write_image.cpp modification_and_write_image.h
	g++ -o modification_and_write_image.o modification_and_write_image.cpp -c

read_image.o: read_image.cpp read_image.h
	g++ -o read_image.o read_image.cpp -c

clear:
	rm *.o