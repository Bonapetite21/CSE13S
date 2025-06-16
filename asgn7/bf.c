#include "bf.h"

#include "speck.h"

#include <stdlib.h>

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

// From assignment PDF
BloomFilter *bf_create(uint32_t size) {
    // Create new Bloom filter of given size
    BloomFilter *bf = malloc(sizeof(BloomFilter));
    if (bf) {
        // Grimm's Fairy Tales
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        // The Adventures of Sherlock Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The Strange Case of Dr. Jekyll and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    // Free Bloom filter and its contents
    if (bf && *bf) {
        bv_delete(&((*bf)->filter));
        free(*bf);
        *bf = NULL;
    }
}

uint32_t bf_size(BloomFilter *bf) {
    // Return number of bits in filter
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    // Set 3 bits in Bloom filter at hash indices from oldspeak
    bv_set_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf));
    bv_set_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    // Return if true if all 3 bits are 1
    return bv_get_bit(bf->filter, hash(bf->primary, oldspeak) % bf_size(bf))
           && bv_get_bit(bf->filter, hash(bf->secondary, oldspeak) % bf_size(bf))
           && bv_get_bit(bf->filter, hash(bf->tertiary, oldspeak) % bf_size(bf));
}

uint32_t bf_count(BloomFilter *bf) {
    // Count number of set bits
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        count += bv_get_bit(bf->filter, i);
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    // Display contents of Bloom filter
    bv_print(bf->filter);
}
