#include "hamming.h"
#include "bm.h"

#include <stdint.h>


uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    // Get msg to BitMatrix
    BitMatrix *m = bm_from_data(msg, 4);
    // Get product of msg as BitMatrix and G
    BitMatrix *p = bm_multiply(m, G);
    // Covert product to encoded data
    uint8_t encoded = bm_to_data(p); 
    // Free memory
    bm_delete(&m);
    bm_delete(&p);
    // return encoded data
    return encoded;
}

//  Returns  the  lower  nibble  of val
static uint8_t lower_nibble(uint8_t  val) {
    return  val & 0xF;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    // Get code as BitMatrix
    BitMatrix *c = bm_from_data(code, 8);
    // Get prodcut of code as BitMatrix and Ht
    BitMatrix *p = bm_multiply(c, Ht);
    // Convert product to data
    uint8_t wrong = bm_to_data(p); 
    // From TA, create lookup table
    HAM_STATUS l_table[16] = {HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2, HAM_ERR, 1, 0, HAM_ERR};
    // Get result by cross referencing product to lookup table
    HAM_STATUS r = l_table[wrong]; 
    // if result is HAMM_OK then set msg to lower nibble of code and return result
    if (r == HAM_OK) {
        *msg = lower_nibble(code);
        return r;
    }
    // if result is HAMM_ERR then return result
    if (r == HAM_ERR) {
        return r;
    }
    // Flip bit of code at index given by result and return lower nibble of code
    code ^= 1 << r;
    *msg = lower_nibble(code);
    return HAM_CORRECT;
}
