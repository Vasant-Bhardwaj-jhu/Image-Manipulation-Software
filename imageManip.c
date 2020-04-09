#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ppm_io.h"
#include "imageManip.h"

void exposure(FILE *in1, FILE *in2, double n){
  Image *im1 = read_ppm(in1);
  for (int r = 0; r < (im1->cols * im1->rows); r++) {
    if((int) im1->data[r].r * pow(2, n) > 255){
      im1->data[r].r = 255;
    }
    else{
      im1->data[r].r = im1->data[r].r * pow(2, n);
    }
    if((int) im1->data[r].g * pow(2, n) > 255){
      im1->data[r].g = 255;
    }
    else{
      im1->data[r].g = im1->data[r].g * pow(2, n);
    }
    if((int) im1->data[r].b * pow(2, n) > 255){
      im1->data[r].b = 255;
    }
    else{
      im1->data[r].b = im1->data[r].b * pow(2, n);
    }
  }
  write_ppm(in2, im1);
}

void aBlending(FILE *in1, FILE *out_file, FILE *in3, double n){
  Image *im1 = read_ppm(in1);
  Image *im2 = read_ppm(in3);
  Image * out = create_empty(im1->rows, im1->cols);
  for(int i = 0; i < (im1->cols * im1->rows); i++){
      out->data[i].r = im1->data[i].r*n +im2->data[i].r*(1-n);
      out->data[i].g = im1->data[i].g*n +im2->data[i].g*(1-n);
      out->data[i].b = im1->data[i].b*n +im2->data[i].b*(1-n);
  }
  write_ppm(out_file, out);
  free(out);
}

void zoom_in(FILE*in1, FILE*in2) {
    Image *im1 = read_ppm(in1);
    int r = im1->rows;
    int c = im1->cols;

    Image * out = create_empty(r * 2, c * 2);
    int size = r * c;

    int pos = 0;
    for (int i = 0; i < size * 4; i += (c * 4)){
        for (int j = i; j < (i + c * 2); j += 2) {
            Pixel p = im1->data[pos];
            out->data[j] = p;
            out->data[j + 1] = p;
            out->data[j + (c * 2)] = p;
            out->data[j + (c * 2) + 1] = p;
            pos++;
        }
    }


    write_ppm(in2, out);
    free(out);
}

void zoom_out(FILE* in1, FILE*in2) {
    Image *im1 = read_ppm(in1);
    int r = im1->rows;
    int c = im1->cols;

    Image * out = create_empty(r / 2, c / 2);
    int size = r * c;
    int pos = 0;

    for (int i = 0; i <= size; i += (c * 4)){
        for (int j = i; j <= (i + c * 2); j += 2) {

            Pixel p;
            p.r = (im1->data[j].r + im1->data[j + 1].r + im1->data[j + (c * 2)].r + im1->data[j + (c * 2) + 1].r) / 4;
            p.b = (im1->data[j].b + im1->data[j + 1].b + im1->data[j + (c * 2)].b + im1->data[j + (c * 2) + 1].b) / 4;
            p.g = (im1->data[j].g + im1->data[j + 1].g + im1->data[j + (c * 2)].g + im1->data[j + (c * 2) + 1].g) / 4;
            out->data[pos] = p;
            pos++;
        }
    }

    write_ppm(in2, out);
    free(out);
}

void pointillism(FILE *in1, FILE *in2){
    Image *im1 = read_ppm(in1);
    int size = im1->cols * im1->rows;
    int width = im1->cols;

    for (int j = 0; j < (size * 0.03); j++) {
        int pos = rand() % (size + 1);
        int r = rand() % 5 + 1;
        Pixel p = im1->data[pos];

        // Optimization, avoids scanning through whole image
        // check possible underflow
        int start = pos - (width * (r+1));
        if (start < 0) {
            start = 0;
        }
        // check overflow
        int end = pos + (width * (r+1));
        if (end > size){
            end = size;
        }

        for (int i = start; i < end; i++){
            // (x - center_x)^2 + (y - center_y)^2 < radius^2
            if (pow((i % width - pos % width), 2) + pow((i / width  - pos / width),2) <= pow(r, 2)) {
                im1->data[i] = p;
            }
        }
    }

    write_ppm(in2, im1);
}

void swirl(FILE *in1, FILE *in2, int c_x, int c_y, int strength) {
    Image *im1 = read_ppm(in1);
    Image * out = create_empty(im1->rows, im1->cols);

    int width = im1->cols;
    int size = im1->cols * im1->rows;

    int x,y,mod_x,mod_y,new_x,new_y,new_i;

    for (int i = 0; i < size; i++) {

        x = i % width;
        mod_x = x - c_x;
        y = i / width;
        mod_y = y - c_y;

        double alpha = sqrt(pow(mod_x, 2) + pow(mod_y, 2)) / (double) strength;
        double p1x = (mod_x*cos(alpha));
        double p1y = (mod_y*sin(alpha));
        double p2x = (mod_x*sin(alpha));
        double p2y = (mod_y*cos(alpha));
        new_x = p1x - p1y + c_x;
        new_y = p2x + p2y + c_y;
        if(new_x < im1->cols && new_x >= 0 && new_y < im1->rows && new_y >= 0){
          new_i = new_x + new_y * width;
          if (new_i < size && new_i > 0) {
            out->data[i] = im1->data[new_i];
          }
        }
        
    }

    write_ppm(in2, out);
    free(out);
}

double *Gaussian(double x){
  int n = x*10;
  if(n % 2 == 0){
    n++;
  }
  int y = (n+1)/2;
  double *gArray = malloc(sizeof(double) * n *n);
  double *sArray = malloc(sizeof(double) * y *y);
  //gets sample array
  for(int i = 0; i < y; i++){
    for(int j = 0; j < y; j++){
      sArray[(i*y)+j] = (1.0 / (2.0 * 3.1415926 * (x*x))) * exp( -((i*i)+(j*j)) / (2 * (x*x)));
      //printf("%f ", sArray[(i*y)+j]);
    }
    //printf("\n");
  }
  //printf("\n");

  //copies array to bottom right quadrant
  int a = 0;
  for(int i = y-1; i < n ; i++){
    for(int j = y-1; j < n; j++){
      gArray[(i*n) + j] = sArray[a];
      a++;
      //printf("%d is: %f ",(i*n) +j, gArray[(i*n)+j]);
    }
    //printf("\n");
  }

  //printf("\n");
  //populates reverse array to bottom right quadrant
  for(int i = y-1; i < n; i ++){
    for(int j = 0; j < y-1; j++){
      gArray[(i*n) + j] = gArray[((i+1)*n) - (j+1)];
      //printf("%d is: %f ",(i*n) +j, gArray[(i*n)+j]);
    }
    //printf("\n");
  }
  //printf("\n");
  //populates top half with reverse of bottom half
  for(int i = 0; i < y-1; i++){
    for(int j = 0; j < n ; j++){
      gArray[(i*n) + j] = gArray[n*n-(i*n +j+1)];
      //printf("%d is: %f ",(i*n) +j, gArray[(i*n)+j]);
    }
    //printf("\n");
  }
  /*prints final array
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n ; j++){
      printf("%f ", gArray[(i*n)+j]);
    }
    printf("\n");
  }*/
  return gArray;
}
Pixel filter(double * gMatrix, Image *im1, int pos, int gSize){
  Pixel vals;
  double red = 0;
  double green = 0;
  double blue = 0;
  double sum = 0;
  Pixel test[gSize*gSize];
  //initializing pixel matrix array to 0
  for(int i =0; i <gSize*gSize; i++){
    test[i].r = 0;
    test[i].g = 0;
    test[i].b = 0;
  }
  int center = gSize*gSize/2;
  for(int i = -gSize/2; i <= gSize/2; i++){
    for(int j = -gSize/2; j<= gSize/2; j++){
      if(pos +(i*im1->cols)+j >= 0 && (pos +(i*im1->cols)+j) < (im1->rows*im1->cols)){
        if((pos % im1->cols)+j < im1->cols &&(pos % im1->cols)+ j >= 0){
           test[center+(i*gSize)+j].r = im1->data[pos +(i*im1->cols)+j].r;
           test[center+(i*gSize)+j].g = im1->data[pos +(i*im1->cols)+j].g;
           test[center+(i*gSize)+j].b = im1->data[pos +(i*im1->cols)+j].b;
        }
      }
    }
  }
  for(int i = 0; i <gSize*gSize; i++){
    red += test[i].r * gMatrix[i];
    green += test[i].g * gMatrix[i];
    blue += test[i].b *gMatrix[i];
    sum += gMatrix[i];
  }
  vals.r = red/sum;
  vals.g = green/sum;
  vals.b = blue/sum;
  //printf("red %f green %f blue %f sum %f vals.r %u vals.g %u vals.b %u\n",red, green, blue, sum, vals.r, vals.g, vals.b);
  return vals;
}

void blur(FILE *im1, FILE *im2, double sigma){
  Image *im = read_ppm(im1);
  int n = 10* sigma;
  if(n % 2 == 0){
    n++;
  }
  double *gMatrix = Gaussian(sigma);
  for(int i = 0; i < im->rows*im->cols; i++){
    Pixel p = filter(gMatrix, im, i, n);
    // printf("new: %u %u %u \n", p.r, p.g, p.b);
    im -> data[i].r = p.r;
    im -> data[i].g = p.g;
    im -> data[i].b = p.b;
  }
  write_ppm(im2, im);
}