
#include <stdio.h>
#include "ppm_io.h"


 // Reads file using ppm_io, sends to correct function in imageManip.c
 // Handles very basic read errors/command line errors
int main( int argc, char *argv[] ) {
    return select_function(argc, argv);
}