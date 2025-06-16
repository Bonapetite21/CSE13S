#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitVector {
    uint32_t length; 
    uint8_t *vector;
};

BitVector *bv_create(uint32_t length) {
    // Allocate memory and fill array with 0's
    BitVector *s = (BitVector *) calloc(1, sizeof(BitVector));
    // If calloc then set rows and columns
    if (s != NULL) {
        s->length = length;
        // If divisible by 8 then make an even matrix 
        if (length % 8 == 0) { 
            s->vector = (uint8_t *) calloc(length / 8, sizeof(uint8_t));
        // else add a byte make an odd matrix
        } else { 
            s->vector = (uint8_t *) calloc(length / 8 + 1, sizeof(uint8_t));
        }
        // if NULL 
        if (!s->vector) { 
            // free s
            free(s);
            // set NULL 
            s = NULL;
        }
    }
    return s;
}

void bv_delete(BitVector **v) {
    // if v or pointer v are NULL
    if (v == NULL || *v == NULL) {
        return;
        
    }
    // Free memory
    free((*v)->vector);
    free(*v);
    // Set to NULL
    *v = NULL;
    return;
}

uint32_t bv_length(BitVector *v) {
    return v->length;
}

void bv_set_bit(BitVector *v, uint32_t i) {
    // Set ith position to 1 != 1
    v->vector[i / 8] |= (1 << (i % 8));
}

void bv_clr_bit(BitVector *v, uint32_t i) {
    // Set bit i = 0
    v->vector[i / 8] &= ~(1 << (i % 8));
}

void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    // i XOR bit
    v->vector[i / 8] ^= (bit << (i % 8));
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
    // return bit = i
    return (v->vector[i / 8] >> (i % 8)) & 1;
}

void bv_print(BitVector *v) {
    // Followed closely from previous assignments
    for (uint32_t i = 0; i < v->length; i++) {
        printf("%d ", (v->vector[i / 8] >> (i % 8)) & 1);
    }
    printf("\n");
}
