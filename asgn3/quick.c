#include "stack.h"
#include "queue.h"

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "support.h"


uint32_t max_stack_size;
uint32_t max_queue_size;


int64_t partition(uint32_t *arr, int64_t lo, int64_t hi) {
    int64_t pivot = arr[lo + ((hi - lo) / 2)];
    int64_t i = lo - 1;
    int64_t j = hi + 1;
    while (i < j) {
        i++;
        while (arr[i] < pivot) {
            i++;
            comparisons++;
        } 
        j--;
        comparisons++;
        while (arr[j] > pivot) {
            j--;
            comparisons++;
        }
        comparisons++;
        if (i < j) {
            uint32_t temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            moves += 3;
        }
    }
    return j;
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    comparisons = 0;
    moves = 0;
    int64_t lo = 0;
    int64_t hi = n - 1;
    Stack *s = stack_create(n);
    stack_push(s, lo);
    stack_push(s, hi);
    while (stack_empty(s) == false) {
        max_stack_size = (max_stack_size > stack_size(s)) ? max_stack_size:stack_size(s);
        stack_pop(s, &hi);
        stack_pop(s, &lo);
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            stack_push(s, lo);
            stack_push(s, p);
        }
        if (hi > p + 1) {
            stack_push(s, p + 1);
            stack_push(s, hi);
        }
    }
    stack_delete(&s);
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    comparisons = 0;
    moves = 0;
    int64_t lo = 0;
    int64_t hi = n - 1;
    Queue *q = queue_create(n);
    enqueue(q, lo);
    enqueue(q, hi);
    while (queue_empty(q) == false) {
        max_queue_size = (max_queue_size > queue_size(q)) ? max_queue_size:queue_size(q);
        dequeue(q, &lo);
        dequeue(q, &hi);
        int64_t p = partition(A, lo, hi);
        if (lo < p) {
            enqueue(q, lo);
            enqueue(q, p);
        }
        if (hi > p + 1) {
            enqueue(q, p + 1);
            enqueue(q, hi);
        }
    }
    queue_delete(&q);
}
