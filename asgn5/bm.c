#include "bm.h"
#include "bv.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct BitMatrix {
    uint32_t rows; 
    uint32_t cols; 
    BitVector *vector; 
};

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    // Allocate memory and fill array with 0's
    BitMatrix *s = (BitMatrix *) calloc(1, sizeof(BitMatrix));
    // If calloc then set rows and columns
    if (s != NULL) { 
        s->rows = rows; 
        s->cols = cols;
        // Create vector
        s->vector = bv_create(rows * cols); 
        // if vector is NULL
        if (!s->vector) { 
            // free s
            free(s);
            // return NULL
            return NULL;
        }
    }
    return s; 
}

void bm_delete(BitMatrix **m) {
    // if m and pointer m are not NULL
    if (m != NULL && *m != NULL) { 
        // delete vector
        bv_delete(&((*m)->vector));
        // free m
        free(*m);
        // set poiinter to Null
        *m = NULL;
    }
    // return
    return;
}

uint32_t bm_rows(BitMatrix *m) {
    // return rows
    return m->rows;
}

uint32_t bm_cols(BitMatrix *m) {
    // returns columns
    return m->cols;
}

void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    // set rows and columns
    bv_set_bit(m->vector, r * m->cols + c);
}

void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    // clear rows and colums
    bv_clr_bit(m->vector, r * m->cols + c);
}

uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    // return rows and columns
    return bv_get_bit(m->vector, r * m->cols + c);
}

BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    // Make matrix 1 x columns
    BitMatrix *data = bm_create(1, length);
    // if data
    if (data) {
        // data set with correct number of bits
        for (uint32_t b = 0; b < length; b++) {
            if (byte & (1 << b)) {
                bm_set_bit(data, 0, b);
            }
        }
    }
    // return data
    return data;
}

uint8_t bm_to_data(BitMatrix *m) {
    uint8_t data = 0;
    // for b 0 to 8 
    for (int b = 0; b < 8; b++) {
        // if the bit at 0,b is 1 
        if (bm_get_bit(m, 0, b) == 1) {
            // left shift on 1 and or that with data
            data |= (1 << b);
        }
    }
    // return data
    return data;
}

// Citing Eric's session
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    // If matrix A and B can be multiplied
    if (A->cols != B->rows) {
        // return NULL
        return NULL;
    }
    // Make matrix product
    BitMatrix *product = bm_create(A->rows, B->cols);
    // Matrix A and B used to make product 
    int multiply = 0;
    for (uint32_t i = 0; i < product->rows; i++) {
        for (uint32_t j = 0; j < product->cols; j++) {
            for (uint32_t k = 0; k < B->rows; k++) {
                multiply = bm_get_bit(A, i, k) & bm_get_bit(B, k, j);
                bv_xor_bit(product->vector, (i * product->cols) + j, multiply);
            }
        }
    }
    // return product
    return product; 
}

void bm_print(BitMatrix *m) {
    // Followed closely to previous assignments
    for (uint32_t i = 0; i < m->rows; i++) {
        for (uint32_t j = 0; j < m->cols; j++) {
            printf("%d ", bm_get_bit(m, i, j));
        }
        printf("\n");
    }
}
