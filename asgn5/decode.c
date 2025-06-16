#include "bm.h"
#include "hamming.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define OPTIONS "hi:o:v"

static void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A Hamming(8, 4) systematic code decoder.\n"
        "\n"
        "USAGE\n"
        "  %s ./decode [-h] [-v] [-i infile] [-o outfile]\n"
        "\n"
        "OPTIONS\n"
        "  -h             Program usage and help.\n"
        "  -v             Print statistics of decoding to stderr.\n"
        "  -i infile      Input data to decode.\n"
        "  -o outfile     Output of decoded data.\n",
        exec);
}

//  Packs  two  nibbles  into a byte
uint8_t  pack_byte(uint8_t  upper , uint8_t  lower) {
    return (upper  << 4) | (lower & 0xF);
}

int main(int argc, char **argv) {
    // Getting options from user to read, write and/or help menu 
    FILE *infile = stdin;
    FILE *outfile = stdout;
    int v = 0;
    int c = 0;
    while ((c = getopt(argc, argv, OPTIONS)) != -1) {
        switch (c) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'v': v = 1; break;
        case 'h': usage(argv[0]); return EXIT_SUCCESS;
        default: usage(argv[0]); return EXIT_FAILURE;
        }
    }

    // Construct Ht = H transposed matrix
    BitMatrix *Ht = bm_create(8, 4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i != j) {
                bm_set_bit(Ht, i, j);
            }
        }
    }
    for (int i = 4; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            if (i - 4 == j) {
                bm_set_bit(Ht, i, j);
            }
        }
    }

    // Used for testing
    // bm_print(Ht);

    // While every byte from the infile 
    int byte_l;
    int byte_u;
    int tot_uncorrected = 0;
    int tot_corrected = 0;
    int tot_bytes_p = 0;
    while ((byte_l = fgetc(infile)) != EOF) {
        byte_u = fgetc(infile);
        uint8_t d_nibble_l;
        uint8_t d_nibble_u;
        HAM_STATUS s1 = ham_decode(Ht, byte_l, &d_nibble_l);
        HAM_STATUS s2 = ham_decode(Ht, byte_u, &d_nibble_u);
        fputc(pack_byte(d_nibble_u, d_nibble_l), outfile);
        if (s1 == HAM_ERR) {
            tot_uncorrected++;
        } else if (s1 == HAM_CORRECT) {
            tot_corrected++;
        }
        if (s2 == HAM_ERR) {
            tot_uncorrected++;
        } else if (s2 == HAM_CORRECT) {
            tot_corrected++;
        }
        tot_bytes_p += 2;
    }
    if (v == 1) {
        printf("Total bytes processed: %d\n", tot_bytes_p);
        printf("Uncorrected errors: %d\n", tot_uncorrected);
        printf("Corrrected errors: %d\n", tot_corrected);
        printf("Error rate: %f\n", (float) tot_uncorrected/ (float) tot_bytes_p);
    }
    // Close files and free memory
    fclose(infile);
    fclose(outfile);
    bm_delete(&Ht);

    return EXIT_SUCCESS;
}

