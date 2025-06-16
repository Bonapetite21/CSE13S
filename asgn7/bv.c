#include "bv.h"

#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    // Create new bit vector
    BitVector *bv = calloc(1, sizeof(BitVector));
    if (bv) {
        bv->length = length;
        if (length % 8) {
            // Add an extra byte if number of bits is not divisible by 8
            bv->vector = calloc(length / 8 + 1, sizeof(uint8_t));
        } else {
            bv->vector = calloc(length / 8, sizeof(uint8_t));
        }
        if (!bv->vector) {
            free(bv);
            bv = NULL;
        }
    }
    return bv;
}

void bv_delete(BitVector **bv) {
    // Free bit vector and its contents
    if (bv && *bv) {
        free((*bv)->vector);
        free(*bv);
        *bv = NULL;
    }
}

uint32_t bv_length(BitVector *bv) {
    // Return number of bits
    return bv->length;
}

void bv_set_bit(BitVector *bv, uint32_t i) {
    // Set bit at index i
    bv->vector[i / 8] |= (1 << (i % 8));
}

void bv_clr_bit(BitVector *bv, uint32_t i) {
    // Clear bit at index i
    bv->vector[i / 8] &= ~(1 << (i % 8));
}

uint8_t bv_get_bit(BitVector *bv, uint32_t i) {
    // Return bit at index i
    return (bv->vector[i / 8] >> (i % 8)) & 1;
}

void bv_print(BitVector *bv) {
    // Display contents of bit vector
    for (uint32_t i = 0; i != bv_length(bv); i++) {
        printf("%d ", (bv->vector[i / 8] >> (i % 8)) & 1);
    }
    printf("\n");
}
