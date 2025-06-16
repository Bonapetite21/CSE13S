#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KB      1024
#define WORD    "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]+)*"
#define OPTIONS "hsmt:f:"

static void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "  A word filtering program for the GPRSC.\n"
        "  Filters out and reports bad words parsed from stdin.\n"
        "\n"
        "USAGE\n"
        "  %s [-hsm] [-t size] [-f size]\n"
        "\n"
        "OPTIONS\n"
        "  -h           Program usage and help.\n"
        "  -s           Print program statistics.\n"
        "  -m           Enable move-to-front rule.\n"
        "  -t size      Specify hash table size (default: 10000).\n"
        "  -f size      Specify Bloom filter size (default: 2^20).\n",
        exec);
}

int main(int argc, char **argv) {
    uint32_t fsize = 1048576;
    uint32_t tsize = 10000;
    int mtf = 0;
    int stats = 0;
    int c;
    while ((c = getopt(argc, argv, OPTIONS)) != -1) {
        switch (c) {
        case 'f': fsize = atoi(optarg); break;
        case 't': tsize = atoi(optarg); break;
        case 'm': mtf = 1; break;
        case 's': stats = 1; break;
        case 'h': usage(argv[0]); return EXIT_FAILURE;
        default: usage(argv[0]); return EXIT_SUCCESS;
        }
    }

    // Check for invalid bf/ht size
    if (!fsize || !tsize) {
        fprintf(stderr, "Invalid size.\n");
        return EXIT_FAILURE;
    }

    // Create bf and ht
    BloomFilter *bf = bf_create(fsize);
    HashTable *ht = ht_create(tsize, mtf);

    // Add badspeak words to bf and ht
    FILE *btxt = fopen("badspeak.txt", "r");
    char buf1[KB], buf2[KB];
    while (fscanf(btxt, "%s", buf1) != -1) {
        bf_insert(bf, buf1);
        ht_insert(ht, buf1, NULL);
    }

    // Add newspeak translations to bf and ht
    FILE *ntxt = fopen("newspeak.txt", "r");
    while (fscanf(ntxt, "%s %s", buf1, buf2) != -1) {
        bf_insert(bf, buf1);
        ht_insert(ht, buf1, buf2);
    }

    // Create lists for storing transgressions found
    LinkedList *bfound = ll_create(mtf);
    LinkedList *nfound = ll_create(mtf);

    // Compile regex
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    // Parse words from st
    char *w = NULL;
    while ((w = next_word(stdin, &re)) != 0) {
        for (int i = 0; i < (int) strlen(w); i++) {
            w[i] = tolower(w[i]); // Make word lowercase
        }
        if (!bf_probe(bf, w)) {
            continue; // Ignore word if bf returns false
        } else {
            // Otherwise, check if word is in ht
            Node *n = ht_lookup(ht, w);
            if (n) {
                // Record transgression if word is in ht
                if (n->newspeak) {
                    ll_insert(nfound, n->oldspeak, n->newspeak);
                } else {
                    ll_insert(bfound, n->oldspeak, n->newspeak);
                }
            }
        }
    }
    clear_words();
    regfree(&re);

    // If stats enabled by user then print stats
    if (stats == true) {
        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %f\n", (double) links / (double) seeks);
        printf("Hash table load: %f%%\n", 100 * (double) ht_count(ht) / (double) ht_size(ht));
        printf("Bloom filter load: %f%%\n", 100 * (double) bf_count(bf) / (double) bf_size(bf));
    }

    // Free memory for bf and ht
    bf_delete(&bf);
    ht_delete(&ht);

    if (stats == false) {
        // "If the citizen is accused of thoughtcrime
        // and requires counceling on proper Rightspeak ..."
        if (ll_length(bfound) > 0 && ll_length(nfound) > 0) {
            // Print mixspeak message
            printf("%s", mixspeak_message);
        }

        // "If the citizen is accused soley if thoughtcrime ..."
        if (ll_length(bfound) > 0 && ll_length(nfound) == 0) {
            // Print badspeak message
            printf("%s", badspeak_message);
        }

        // "If the citizen only requires counceling ..."
        if (!ll_length(bfound) && ll_length(nfound)) {
            // Print newspeak message
            printf("%s", goodspeak_message);
        }

        // Print the lists of transgressions found
        ll_print(bfound);
        ll_print(nfound);
    }

    // Free memory for lists of transgressions found
    ll_delete(&bfound);
    ll_delete(&nfound);

    // Close files
    fclose(btxt);
    fclose(ntxt);

    return EXIT_SUCCESS;
}
