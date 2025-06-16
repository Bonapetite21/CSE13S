#include "ll.h"

#include <stdlib.h>
#include <string.h>

uint64_t seeks = 0;
uint64_t links = 0;

struct LinkedList {
    uint32_t length;
    Node *head;
    Node *tail;
    bool mtf;
};

LinkedList *ll_create(bool mtf) {
    // Create a new linked list
    LinkedList *ll = malloc(sizeof(LinkedList));
    if (ll) {
        ll->length = 0;
        ll->mtf = mtf;
        ll->head = node_create("HEAD", NULL);
        ll->tail = node_create("TAIL", NULL);
        if (!ll->head || !ll->tail) {
            free(ll);
            ll = NULL;
            return NULL;
        }
        ll->head->next = ll->tail;
        ll->tail->prev = ll->head;
    }
    return ll;
}

void ll_delete(LinkedList **ll) {
    // Free linked list and its contents
    if (ll && *ll) {
        for (Node *n = (*ll)->head; n != NULL;) {
            Node *saved = n;
            n = n->next;
            node_delete(&saved);
        }
        free(*ll);
        *ll = NULL;
    }
}

uint32_t ll_length(LinkedList *ll) {
    // Return number of nodes not including sentinel nodes
    return ll->length;
}

Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    // Return node if found, null otherwise
    seeks++;
    Node *n = ll->head->next;
    while (n != ll->tail) {
        if (!strcmp(n->oldspeak, oldspeak)) { // (Consider changing later)
            // Move-to-front technique inspired by Eugene's section
            if (ll->mtf) {
                // Bridge over n
                n->prev->next = n->next;
                n->next->prev = n->prev;
                // Insert n at front
                n->next = ll->head->next;
                n->prev = ll->head;
                ll->head->next = n;
                n->next->prev = n;
            }
            return n;
        }
        n = n->next;
        links++;
    }
    return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    // Insert node with given oldspeak and newspeak
    Node *n = node_create(oldspeak, newspeak);
    if (ll_lookup(ll, oldspeak) || !n) {
        node_delete(&n);
        return; // Do not insert if already exists or if node_create fails
    }
    // Insert n at front
    n->next = ll->head->next;
    n->prev = ll->head;
    ll->head->next = n;
    n->next->prev = n;
    ll->length++;
}

void ll_print(LinkedList *ll) {
    // Display contents of linked list ll
    for (Node *n = ll->head->next; n != ll->tail; n = n->next) {
        node_print(n);
    }
}
