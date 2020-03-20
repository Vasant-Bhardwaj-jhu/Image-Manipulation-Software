CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra -g


main:
	make project

project: imageManip.o ppm_io.o project.o
	$(CC) $(CFLAGS) imageManip.o ppm_io.o project.o -o project

project.o: project.c ppm_io.h imageManip.h
	$(CC) $(CFLAGS) -c project.c

demo: demo_ppm.o ppm_io.o
	$(CC) demo_ppm.o ppm_io.o -o demo

demo_ppm.o: demo_ppm.c ppm_io.h
	$(CC) $(CFLAGS) -c demo_ppm.c

ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

imageManip.o: imageManip.c imageManip.h
	$(CC) $(CFLAGS) -c imageManip.c

clean:
	rm -f *.o demo
