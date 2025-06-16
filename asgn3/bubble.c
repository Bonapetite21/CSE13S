#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include "support.h"


void bubble_sort(uint32_t *A, uint32_t n) {
    comparisons = 0;
    moves = 0;
    bool swapped = true;

    while (swapped) {
        swapped = false;
    
        for (uint32_t i = 1; i < n; i++) {
            comparisons += 1;
            if (A[i] < A[i - 1]) {
                int temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                swapped = true;
                moves += 3;
            }
        }
        n--;
    }
}
