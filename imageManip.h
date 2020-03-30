#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ppm_io.h"

/*takes an images an input, then alters the exposure as 
is stated by the user*/
void exposure(FILE *im1, FILE *im2, double n);
/*merges two images together*/
void aBlending(FILE *im1, FILE *im2, FILE *im3, double n);
/*zooms into image, puting it into a new image*/
void zoom_in(FILE*im1, FILE*im2);
/*zooms out of image, putting it in new image*/
void zoom_out(FILE*im1, FILE*im2);
/*applys pointillism techniques to image*/
void pointillism(FILE *in1, FILE *in2);
/*swirls image on certain point (x,y) by a certain strength*/
void swirl(FILE *im1, FILE *im2, int x, int y, int strength);
/*creates a gaussian matrix*/
double **Gaussian(double x);
/*filters one pixel to get blurred output*/
Pixel convolve(double ** gMatrix, Pixel p);
/*applys blur, usese Gaussian and convolve*/
void blur(FILE *im1, FILE *im2, double sigma);
