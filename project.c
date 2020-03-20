
#include <stdio.h>
#include "ppm_io.h"
#include "imageManip.h"


 // Reads file using ppm_io, sends to correct function in imageManip.c
 // Handles very basic read errors/command line errors
int main( int argc, char *argv[] ) {
    return 0;
    FILE * in = fopen("building.ppm", "rb");
    FILE * out = fopen("treeTestOutput.ppm", "w");
    Image *test = read_ppm(in);
    write_ppm(out, test);
    printf("running");
    //FILE * in = fopen("trees.ppm", "rb");
    
    //exposure(in, out, 1.0);
    return 0;
}
