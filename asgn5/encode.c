#include "bm.h"
#include "hamming.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define OPTIONS "hi:o:"

static void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Hamming(8, 4) systematic code generator.\n"
        "\n"
        "USAGE\n"
        "  %s ./encode [-h] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -i infile      Input data to encode."
        "  -o outfile     Output of encoded data.\n",
        exec);
}

//  Returns  the  lower  nibble  of val
uint8_t  lower_nibble(uint8_t  val) {
    return  val & 0xF;
}

 //  Returns  the  upper  nibble  of val
uint8_t  upper_nibble(uint8_t  val) {
    return  val  >> 4;
}

int main(int argc, char **argv) {
    // Getting options from user to read, write and/or help menu 
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int c = 0;
    while ((c = getopt(argc, argv, OPTIONS)) != -1) {
        switch (c) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    // Construct G = generator matrix
    BitMatrix *G = bm_create(4, 8);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                bm_set_bit(G, i, j);
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 4; j < 8; j++) {
            if (i != j - 4) {
                bm_set_bit(G, i, j);
            }
        }
    }

    // Used for testing
    // bm_print(G);

    // While every byte from the infile 
    int byte;
    while ((byte = fgetc(infile)) != EOF) {
        // Put encoded lower nible to outfile 
        fputc(ham_encode(G, lower_nibble(byte)), outfile);
        // Put encoded upper nible to outfile 
        fputc(ham_encode(G, upper_nibble(byte)), outfile);
    }
    // Close files and free memory
    fclose(infile);
    fclose(outfile);
    bm_delete(&G);

    return EXIT_SUCCESS;
}

