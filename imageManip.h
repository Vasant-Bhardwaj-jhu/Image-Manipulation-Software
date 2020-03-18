#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "ppm_io.h"

/*takes an images an input, then alters the exposure as 
is stated by the user*/
void Exposure(Image *im, float n);
void aBlending(Image *im1, Image *im2, Image *im3, int x);
