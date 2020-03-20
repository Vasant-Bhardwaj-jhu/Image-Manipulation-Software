#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ppm_io.h"
#include "imageManip.h"


void exposure(FILE *in1, FILE *in2, double n){
  Image *im1 = read_ppm(in1);
  Image *im2 = NULL;
  for (int r = 0; r < im2->rows; r++) {
    for (int c = 0; c < im2->cols; c++) {
      im2->data[(r*im2->cols) + c].r = im1->data[(r*im1->cols) + c].r * pow(2, n);
      im2->data[(r*im2->cols) + c].g = im1->data[(r*im1->cols) + c].r * pow(2, n);
      im2->data[(r*im2->cols) + c].b = im1->data[(r*im1->cols) + c].r * pow(2, n);
    }
  }
  write_ppm(in2, im2);
}
void aBlending(FILE *in1, FILE *in2, FILE *in3, int n){
  Image *im1 = read_ppm(in1);
  Image *im2 = read_ppm(in2);
  Image *im3 = read_ppm(in3);
  for (int r = 0; r < im2->rows; r++) {
    for (int c = 0; c < im2->cols; c++) {
      im2->data[(r*im2->cols) + c].r = im1->data[(r*im1->cols) + c].r*n +im3->data[(r*im3->cols) + c].r*(1-n);
      im2->data[(r*im2->cols) + c].g = im1->data[(r*im1->cols) + c].g*n +im3->data[(r*im3->cols) + c].g*(1-n);
      im2->data[(r*im2->cols) + c].b = im1->data[(r*im1->cols) + c].b*n +im3->data[(r*im3->cols) + c].b*(1-n);
    }
  } 
}
