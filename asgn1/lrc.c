#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "philos.h"

// 
// Returns the position of the player to the left.
//
// pos:     The position of the current player.
// players: The number of players in the game.
//
static inline uint8_t left(uint8_t pos, uint8_t players) {
    return ((pos + players - 1) % players);
}

//
// Returns the position of the player to the right.
//
// pos:     The position of the current player.
// players: The number of players in the game.
//
static inline uint8_t right(uint8_t pos, uint8_t players) {
    return ((pos + 1) % players);
}

//
// Faces of the die
//
typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };

int main() {
    int array_currency[14];
    int seed;
    int players = 1;
    int winner = 0;
    int currency_pot = 0;
    int pos = 0;
    int win_condition = 0;

    printf("Random seed: ");
    scanf("%d", &seed);
    srandom(seed);

    printf("How many players?");
    scanf("%d", &players);
    if (players < 1 || players > 14) {
        printf("Number of players must be from 1 to 14");
        return 0;
    }

    for (int i = 0; i < players; i++) {
        array_currency[i] = 3;
    }

    while (winner == 0) {
        int temp = array_currency[pos];
        if (array_currency[pos] == 0) {
            pos = right(pos, players);
            continue; 
        } 
        
        for (int j = 0; j < players; j++) {
            if ((array_currency[j] + currency_pot) >= (players * 3)) {
                printf("winner found\n");
                winner = j;
                win_condition = 1;
                break;
            }
        }
        if (win_condition == 1) {
            printf("breaking out of game\n");
            break;
        }

        printf("%s rolls...", philosophers[pos]);
        for (int k = 0; k < 3; k++) {
            if (temp == 0) {
                break;
            }
            int roll = random() % 6; 
            if (roll == LEFT) {
                printf(" gives $1 to %s", philosophers[left(pos, players)]);
                array_currency[left(pos, players)] += 1;
                array_currency[pos] -= 1;
            } 
            else if (roll == RIGHT) {
                printf(" gives $1 to %s", philosophers[right(pos, players)]);
                array_currency[right(pos, players)] += 1;
                array_currency[pos] -= 1;
            }
            else if (roll == CENTER) {
                printf(" puts $1 in the pot");
                currency_pot += 1;
                array_currency[pos] -= 1;
            }
            else {
                printf(" get a pass");
            }
            temp--;        
        }
        pos = right(pos, players);
    }
    printf("%s wins the $%d pot with $%d left in the bank!\n", philosophers[winner], currency_pot, array_currency[winner]);
    return 0;
}
