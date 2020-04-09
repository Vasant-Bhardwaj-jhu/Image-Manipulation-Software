
#include <stdio.h>
#include "ppm_io.h"
#include "imageManip.h"



// Reads file using ppm_io, sends to correct function in imageManip.c
// Handles read errors/command line errors
int select_function(int argc, char *argv[]){

    // Missing one of the required arguments
    if (argc < 4) {
        kill(1);
    }

    // open input and output file
    FILE * in = fopen(argv[1], "rb");
    FILE * out = fopen(argv[2], "wb");

    // Check their validity
    if (in == NULL) {
        kill(2);
    }
    if (out == NULL) {
        kill(7);
    }

    Image *i = read_ppm(in);

    // Make sure input file will open
    if (i == NULL) {
        kill(3);
    }

    // Function Execution Begins

    // The desired function
    char choice[12];
    strcpy(choice, argv[3]);

    if (strcmp(choice, "exposure") == 0) {
        if (argc != 5) {
            kill(5);
        }
        double n = atof(argv[4]);
        if (n > 255){
            n = 255;
        }
        if (n < -255){
            n = -255;
        }
        exposure(in, out, n);
    }
    else if (strcmp(choice, "blend") == 0) {
        if (argc != 6) {
            kill(5);
        }
        double n = atof(argv[5]);
        if (n > 1 || n < 0){
            kill(6);
        }
        FILE *in2 = fopen(argv[4], "rb");
        if (in2 == NULL) {
            kill(2);
        }
        aBlending(in, out, in2, n);
    }
    else if (strcmp(choice, "zoom_in") == 0) {
        if (argc != 3) {
            kill(5);
        }
        zoom_in(in, out);
    }
    else if (strcmp(choice, "zoom_out") == 0) {
        if (argc != 3) {
            kill(5);
        }
        zoom_out(in, out);
    }
    else if (strcmp(choice, "pointilism") == 0) {
        if (argc != 3) {
            kill(5);
        }
        pointillism(in, out);
    }
    else if (strcmp(choice, "swirl") == 0) {
        if (argc != 7) {
            kill(5);
        }
        int x = atoi(argv[4]);
        int y = atoi(argv[5]);
        int strength = atoi(argv[6]);
        if (s < 0){
            kill(6);
        }
        swirl(in, out, x, y, strength);
    }
    else if (strcmp(choice, "blur") == 0) {
        if (argc != 5) {
            kill(5);
        }

        double sigma = atof(argv[4]);
        blur(in, out, sigma);
    }
    else {
        // invalid requested function
        kill(4);
    }
    return 0;
}


int main( int argc, char *argv[] ) {
    select_function(argc, argv);
    return 0;
}
