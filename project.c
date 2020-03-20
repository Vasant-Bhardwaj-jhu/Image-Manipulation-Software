
#include <stdio.h>
#include "input.h"


 // Reads file using ppm_io, sends to correct function in imageManip.c
 // Handles very basic read errors/command line errors
int main( int argc, char *argv[] ) {
    select_function(argc, argv);
    return 0;
}
