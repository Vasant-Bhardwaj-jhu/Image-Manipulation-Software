#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ppm_io.h"
#include "imageManip.h"


void Exposure (Image *im,float n){
    for (int r = 0; r < im->rows; r++) {
    for (int c = 0; c < im->cols; c++) {
      im->data[(r*im->cols) + c].r *= pow(2.0, n);
      im->data[(r*im->cols) + c].g *= pow(2.0, n);
      im->data[(r*im->cols) + c].b *= pow(2.0, n);
    }
  }
}
void aBlending(Image *im1, Image *im2, Image *im3, int n){
   for (int r = 0; r < im2->rows; r++) {
    for (int c = 0; c < im2->cols; c++) {
      im2->data[(r*im2->cols) + c].r = im1->data[(r*im1->cols) + c].r*n +im3->data[(r*im3->cols) + c].r*(1-n);
      im2->data[(r*im2->cols) + c].g = im1->data[(r*im1->cols) + c].g*n +im3->data[(r*im3->cols) + c].g*(1-n);
      im2->data[(r*im2->cols) + c].b = im1->data[(r*im1->cols) + c].b*n +im3->data[(r*im3->cols) + c].b*(1-n);
    }
  } 
}
