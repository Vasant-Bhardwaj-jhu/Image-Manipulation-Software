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
  long lsize = ftell(fp);
  rewind(fp);
  char buffer[2];
  int color;
  fscanf(fp, "%s %d %d %d", buffer, &im->rows, &im->cols, &color);
  if(buffer[0] != 'P' || buffer[1] != '6'){
    printf("incorrect file format");
    return NULL;
  }
  if(color != 255){
    printf("wrong hue value");
    return NULL;
  }
   Pixel *pix = malloc(sizeof(Pixel) * im->rows * im->cols);
   if (!pix) {
    free(im);
    return NULL;
  }
   im->data = pix;
  for (int r = 0; r < im->rows; r++) {
    for (int c = 0; c < im->cols; c++) {
      fread(&im->data[(r*im->cols) + c], sizeof(Pixel), lsize , fp);
    }
  }

  free(im);
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


