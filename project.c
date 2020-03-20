
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

     FILE * in = fopen(argv[1], "rb");
     FILE * out = fopen(argv[2], "rb");

     if (in == NULL) {
         kill(2);
     }
     if (out == NULL) {
         kill(7);
     }

     Image *i = read_ppm(in);

     if (i == NULL) {
         kill(3);
     }

     // Function Execution Begins
     char choice[12];
     strcpy(choice, argv[3]);

     if (strcmp(choice, "exposure") == 0) {
         float n = strtof(argv[4], NULL);
         exposure(in, out, n);
     }
     else if (strcmp(choice, "aBlending") == 0) {
         int n = atoi(argv[5]);
//        FILE *in2 = fopen(argv[3], "rb");
//        if (in2 == NULL) {
//            kill(2);
//        }
         exposure(in, out, n);
     }
     return 0;
 }


int main( int argc, char *argv[] ) {
    select_function(argc, argv);
    return 0;
}
