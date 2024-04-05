/* 
 * PA2
 * Author: Wesley Lawson - lawsonwe@bc.edu
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fp_analyzer.h"

int main(int argc, char ** argv) {
    char * test = "special";
    union Converter converter;
    if (argc > 1 && strcmp(argv[1], test) == 0) {
        FP_TYPE special_values[] = {INF, -INF, NAN, -NAN};
        int i;
        for (i = 0; i < sizeof(special_values) / sizeof(special_values[0]); ++i) {
            converter.type = special_values[i];
            printf(FP_SCAN_TYPE, converter.type);  
            putchar('\n');
            print_components(converter.u, converter.c);
            putchar('\n');
        }
    } else {
        puts("Please enter a floating-point number or q to quit.");
        printf("> ");
        while (scanf(FP_SCAN_TYPE, &converter.type) == 1) {
            printf(FP_SCAN_TYPE, converter.type);
            putchar('\n');
            print_components(converter.u, converter.c);
            print_reconstitution(converter.c);
            printf("> ");
        }
    }
    return EXIT_SUCCESS;
}
