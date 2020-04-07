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

void aBlending(FILE *in1, FILE *in2, FILE *in3, double n){
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
        new_x = (mod_x * cos(alpha)) - (mod_y * sin(alpha)) + c_x;
        new_y = (mod_x * sin(alpha)) + (mod_y * cos(alpha)) + c_y;
        new_i = new_x + new_y * width;

        if (new_i < size && new_i > 0) {
            out->data[i] = im1->data[new_i];
        }
    }

    write_ppm(in2, out);
    free(out);
}
