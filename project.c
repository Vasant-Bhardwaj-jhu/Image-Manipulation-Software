
#include <stdio.h>
#include "ppm_io.h"
#include "imageManip.h"



// Reads file using ppm_io, sends to correct function in imageManip.c
// Handles very basic read errors/command line errors
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
        double n = atof(argv[4]);
        exposure(in, out, n);
    }
    else if (strcmp(choice, "blend") == 0) {
        double n = atof(argv[5]);
        FILE *in2 = fopen(argv[3], "rb");
        if (in2 == NULL) {
            kill(2);
        }
        aBlending(in, in2, out, n);
    }
    else if (strcmp(choice, "zoom_in") == 0) {
        zoom_in(in, out);
    }
    else if (strcmp(choice, "zoom_out") == 0) {
        zoom_out(in, out);
    }
    else if (strcmp(choice, "pointilism") == 0) {
        pointilism(in, out);
    }
//    else if (strcmp(choice, "swirl") == 0) {
//        int x = atoi(argv[4]);
//        int y = atoi(argv[5]);
//        int strength = atoi(argv[6]);
//        swirl(in, out, x, y, strength);
//    }
//    else if (strcmp(choice, "blur") == 0) {
//        double sigma = atof(argv[4]);
//        blur(in, out, sigma);
//    }
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
