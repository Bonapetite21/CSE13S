#include "gaps.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "support.h"

uint32_t comparisons;
uint32_t moves;

void shell_sort(uint32_t *A, uint32_t n) {
    comparisons = 0;
    moves = 0;
    for (uint32_t i = 0; i < GAPS; i++) {
        uint32_t g = gaps[i];
        for (uint32_t j = g; j < n; j++) {
            uint32_t i = j;
            uint32_t temp = A[j];
            moves++;
            if (i >= g) {
                comparisons++;
            }

            while (i >= g && temp < A[i - g]) {
                A[i] = A[i - g];
                i -= g;
                moves++;
                if (i >= g) {
                   comparisons++;
                }
            }
            A[i] = temp;
            moves++;
        }
    }
}
