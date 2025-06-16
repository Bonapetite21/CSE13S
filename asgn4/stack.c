#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "stack.h"

typedef struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    // Followed closely from asgn 3
    // Allocates memory and createss a stck 
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t)); // void pointer to memory location
        if (!s->items) {
            free(s);
            s = NULL; // sets s to null
        }
    }
    return s;
}

void stack_delete(Stack **s) {

    // deletes stack followeed closely from asgn 3
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {

    // empties stack followeed closely from asgn 3
    if  (s->top == 0) {
        return true;
    }
    return false;
}

bool stack_full(Stack *s) {

    // full stack followeed closely from asgn 3
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

uint32_t stack_size(Stack *s) {
    
    // Size of stack
    return s->top;
}

bool stack_push(Stack *s, uint32_t x) {

    // Followed closely from asgn 3
    if (stack_full(s)) {
        return false;    
    }
    s->items[s->top] = x;
    s->top += 1;
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {

    // Followed closely from asgn 3 
    // Checks if s is on top and will go to the following s from that
    if (s->top) {
        *x = s->items[s->top - 1];
        return true;
    }
    return false;
}

bool stack_pop(Stack *s, uint32_t *x) {

    // Followed closely from asgn 3 
    if (stack_full(s)) {
        return false;    
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

void stack_copy(Stack *dst, Stack *src) {

    // Followed closely from asgn 3 
    // Checks if there is a destination and will index that to items
    if (dst && src) {
        uint32_t len = src->top < dst->capacity ? src->top : dst->capacity;
        for (uint32_t i = 0; i < len; i++) {
            dst ->items[i] = src->items[i];
        }
        dst->top = len;
    }
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {

    // For testing puposes
    // Followed closely from asgn 3 
    for ( uint32_t i = 0; i < s->top ; i++) {
        fprintf(outfile , "%s", cities [s->items [i]]) ;
        if (i + 1 != s->top ) {
            fprintf(outfile , " -> ") ;
        }
    }
    fprintf ( outfile , "\n");
}
