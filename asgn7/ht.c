#include "ht.h"

#include "speck.h"

#include <stdio.h>
#include <stdlib.h>

struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

// From assignment PDF
HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = malloc(sizeof(HashTable));
    if (ht) {
        // Leviathan
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

void ht_delete(HashTable **ht) {
    // Free hash table and its contents
    if (ht && *ht) {
        for (uint32_t i = 0; i < (*ht)->size; i++) {
            ll_delete(&((*ht)->lists[i]));
        }
        free((*ht)->lists);
        free(*ht);
        *ht = NULL;
    }
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

Node *ht_lookup(HashTable *ht, char *oldspeak) {
    // Return node with given oldspeak if found, NULL otherwise
    LinkedList *ll = ht->lists[hash(ht->salt, oldspeak) % ht_size(ht)];
    if (!ll) {
        return NULL; // Don't lookup if linked list does not exist
    }
    return ll_lookup(ll, oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    // Insert given oldspeak and newspeak pair into hash table
    uint32_t index = hash(ht->salt, oldspeak) % ht_size(ht);
    if (ht->lists[index] == NULL) {
        ht->lists[index] = ll_create(ht->mtf);
    }
    ll_insert(ht->lists[index], oldspeak, newspeak);
}

uint32_t ht_count(HashTable *ht) {
    // Count the number of linked lists in hash table
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        count += ht->lists[i] != NULL;
    }
    return count;
}

void ht_print(HashTable *ht) {
    // Display contents of linked list
    for (uint32_t i = 0; i < ht_size(ht); i++) {
        printf("Linked list at index %d ↓\n", i);
        if (ht->lists[i]) {
            ll_print(ht->lists[i]);
        }
    }
}
