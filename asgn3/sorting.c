#include "set.h"
#include "bubble.h"
#include "shell.h"
#include "quick.h"
#include "support.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>


typedef enum {
    BUBBLE,
    SHELL,
    STACK,
    QUEUE,
} SORT;

void (*sorts[4])(uint32_t *A, uint32_t n) = {bubble_sort, shell_sort, quick_sort_stack, quick_sort_queue};

int main(int argc, char **argv) {
    Set enabled = set_empty(); 
    uint32_t n = 100, p = 100, r = 13371453;
    int opt = 0;

    while ((opt = getopt(argc, argv, "habsqQn:p:r:")) != -1) {
        switch (opt) {
            case 'h': guide(); break;
            case 'a':
                enabled = set_insert(enabled, BUBBLE);
                enabled = set_insert(enabled, SHELL);
                enabled = set_insert(enabled, STACK);
                enabled = set_insert(enabled, QUEUE);
                break;
            case 'b': enabled = set_insert(enabled, BUBBLE); break;
            case 's': enabled = set_insert(enabled, SHELL); break;
            case 'q': enabled = set_insert(enabled, STACK); break;
            case 'Q': enabled = set_insert(enabled, QUEUE); break;
            case 'n': n = atoi(optarg); break;
            case 'p': p = atoi(optarg); break;
            case 'r': r = atoi(optarg); break;
            default: guide(); break;
        }
    }

    if (p > n) {
        p = n;
    }

    for (SORT s = BUBBLE; s <= QUEUE; s++) {
        if (set_member(enabled, s)) {

            srandom(r);
            uint32_t A[n];
            for (uint32_t i = 0; i < n; i++) {
                A[i] = random();
            }

            sorts[s](A, n);
            
            switch (s) {
                case 0: printf("Bubble Sort\n"); break;
                case 1: printf("Shell Sort\n"); break;
                case 2: printf("Quick Sort (Stack)\n"); printf("Max stack size: %d\n", max_stack_size); break;
                case 3: printf("Quick Sort (Queue)\n"); printf("Max queue size: %d\n", max_queue_size); break;
            }

            printf("%d elements, %d moves, %d compares\n", n, moves, comparisons);

            // My friend (jtennant) helped me with this, talked about the pseudocode
            for (uint32_t i = 0, j = 0; i < p; i++, j++) {
                if (j == 5) {
                    printf("\n");
                    j = 0;
                }
                printf("%13" PRIu32, A[i]);
            }
            if (p > 0) {
                printf("\n");
            }
        }
    }

    return 0;
}
