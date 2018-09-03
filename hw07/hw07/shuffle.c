#include "shuffle.h"
#include <string.h>
#include <stdio.h>
// You may add more functions in this file.

void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) {
}

void interleave(CardDeck upper_deck, CardDeck lower_deck) {
}

void shuffle(CardDeck orig_deck) {
	int numpairs = -1;

	CardDeck * upper_deck = NULL;
	CardDeck * lower_deck = NULL;

	// allocate memory
	if (upper_deck == NULL || lower_deck == NULL) {
		free(upper_deck);
		free(lower_deck);
	}

	// call divideDeck to fill upper_deck and lower_deck 

	while (numpairs > 0) {
		// for each pairs call interleave
	}
} 
