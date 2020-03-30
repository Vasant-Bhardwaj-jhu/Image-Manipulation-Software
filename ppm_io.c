//Vasant Bhardwaj: Vbhardw2
// __Add your name and JHED above__
// ppm_io.c
// 601.220, Spring 2019
// Starter code for midterm project - feel free to edit/add to this file

#include <assert.h>
#include <stdlib.h>
#include "ppm_io.h"



/* Read a PPM-formatted image from a file (assumes fp != NULL).
 * Returns the address of the heap-allocated Image struct it
 * creates and populates with the Image data.
 */
Image * read_ppm(FILE *fp) {

    // check that fp is not NULL
    assert(fp);
    Image *im = malloc(sizeof(Image));

    fseek (fp, 0, SEEK_END);
    //long lsize = ftell(fp);
    //printf ("%ld\n", lsize);
    rewind(fp);
    char buffer[2];
    int color;
    fscanf(fp, "%s %d %d %d", buffer, &im->cols, &im->rows, &color);
    fgetc(fp);
    //printf("rows:%d %d \n%ld\n", im->rows, im->cols, sizeof(Pixel) * im->rows * im->cols);
    //int x = ftell(fp);
    if(buffer[0] != 'P' || buffer[1] != '6'){
        kill(3);
        return NULL;
    }
    if(color != 255){
        kill(3);
        return NULL;
    }
    Pixel *pix = malloc(sizeof(Pixel) * im->rows * im->cols);
    if (!pix) {
        free(im);
        return NULL;
    }
    //im->data = malloc(sizeof(Pixel) * im->rows * im->cols);
    //printf("before fread rows:%d %d \n%ld\n", im->rows, im->cols, sizeof(Pixel) * im->rows * im->cols);
    fread(pix, sizeof(Pixel),  im->rows * im->cols, fp);
    im->data = pix;
    //printf("after fread rows:%d %d \n%ld\n", im->rows, im->cols, sizeof(Pixel) * im->rows * im->cols);


    return im;
}


/* Write a PPM-formatted image to a file (assumes fp != NULL),
 * and return the number of pixels successfully written.
 */
int write_ppm(FILE *fp, const Image *im) {

    // check that fp is not NULL
    assert(fp);

    // write PPM file header, in the following format
    // P6
    // cols rows
    // 255
    fprintf(fp, "P6\n%d %d\n255\n", im->cols, im->rows);

    // now write the pixel array
    int num_pixels_written = fwrite(im->data, sizeof(Pixel), im->cols * im->rows, fp);

    if (num_pixels_written != im->cols * im->rows) {
        fprintf(stderr, "Uh oh. Pixel data failed to write properly!\n");
    }

    return num_pixels_written;
}

Image * create_empty(int r, int c){
    // Dont forget to free
    Image * out = malloc(sizeof(Image));
    out->rows = r;
    out->cols = c;

    Pixel * dataOut = malloc(sizeof(Pixel) * r * c * 4);
    out->data = dataOut;

    return out;
}

int kill(int error){
    switch (error) {
        case 1:
            fprintf(stderr, " Failed to supply input filename or output filename, or both ");
            break;
        case 2:
            fprintf(stderr, " Specified input file could not be opened ");
            break;
        case 3:
            fprintf(stderr, " Specified input file is not a properly-formatted PPM file, or reading input somehow fails");
            break;
        case 4:
            fprintf(stderr, " No operation name was specified, or operation name specified was invalid ");
            break;
        case 5:
            fprintf(stderr, " Incorrect number of arguments or kind of arguments specified for the specified operation ");
            break;
        case 6:
            fprintf(stderr, " Arguments for the specified operation were out of range for the given input image, or otherwise senseless ");
            break;
        case 7:
            fprintf(stderr, " Specified output file could not be opened for writing, or writing output somehow fails ");
            break;
        case 8:
            fprintf(stderr, " Error condition not specified ");
            break;
    }
    exit(error);
}

