#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *mystrdup(char *s) {
    // Create a duplicate of source string s
    if (s) {
        char *d = malloc(strlen(s) + 1);
        if (d) {
            strcpy(d, s);
        }
        return d;
    }
    return s;
}

Node *node_create(char *oldspeak, char *newspeak) {
    // Create a new node with given oldspeak and newspeak
    Node *n = malloc(sizeof(Node));
    if (n) {
        n->oldspeak = mystrdup(oldspeak);
        n->newspeak = mystrdup(newspeak);
        n->next = NULL;
        n->prev = NULL;
    }
    return n;
}

void node_delete(Node **n) {
    // Free node if not already null
    if (n && *n) {
        if ((*n)->oldspeak) {
            free((*n)->oldspeak);
        }
        if ((*n)->newspeak) {
            free((*n)->newspeak);
        }
        free(*n);
        *n = NULL;
    }
}

void node_print(Node *n) {
    // Display contents of node n
    if (n->newspeak) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
        return;
    }
    printf("%s\n", n->oldspeak);
}
