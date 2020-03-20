CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g



project: project.o ppm_io.o imageManip.o input.o
	$(CC) $(CFLAGS) ppm_io.o imageManip.o input.o project.o -o project

project.o: project.c input.h
	$(CC) $(CFLAGS) -c project.c

demo: demo_ppm.o ppm_io.o
	$(CC) demo_ppm.o ppm_io.o -o demo

demo_ppm.o: demo_ppm.c ppm_io.h
	$(CC) $(CFLAGS) -c demo_ppm.c

input.o: input.c imageManip.h ppm_io.h
	$(CC) $(CFLAGS) -c input.c

ppm_io.o: ppm_io.c
	$(CC) $(CFLAGS) -c ppm_io.c

imageManip.o: imageManip.c ppm_io.h
	$(CC) $(CFLAGS) -c imageManip.c

clean:
	rm -f *.o demo
