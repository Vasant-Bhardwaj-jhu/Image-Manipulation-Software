CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g



# Build project
project: imageManip.o ppm_io.o project.o
	$(CC) $(CFLAGS) imageManip.o ppm_io.o project.o -o project -lm

project.o: project.c ppm_io.h imageManip.h
	$(CC) $(CFLAGS) -c project.c

ppm_io.o: ppm_io.c
	$(CC) $(CFLAGS) -c ppm_io.c

imageManip.o: imageManip.c ppm_io.h
	$(CC) $(CFLAGS) -c imageManip.c

clean:
	rm -f *.o demo
