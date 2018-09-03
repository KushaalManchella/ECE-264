#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// You may add more functions in this file.
int ud_size = 0; // size of upper deck
int ld_size = 0; // size of lower deck

void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) {
	int j = 0; // index of upper_deck 

	for(int i = 0; i < orig_deck.size - 1; i++)
	{
		int index = 0;
		upper_deck[i].size = i+1;
		lower_deck[i].size = orig_deck.size - (i+1);
		for( j = 0; j <= i ; j++)
		{
			upper_deck[i].cards[index] = orig_deck.cards[j];
			ud_size = j;
			index++;
		}
		index = 0;
		for( j = j; j < orig_deck.size ; j++)
		{		
			lower_deck[i].cards[index] = orig_deck.cards[j];
			ld_size = j;
			index++;

		}
	}


}

void _recursion(CardDeck upper_deck, CardDeck lower_deck, CardDeck new_deck, int ind_low, int ind_up, int i){
	if(upper_deck.size == ind_up && lower_deck.size == ind_low) // base case 
	{
		print_deck(new_deck);
		printf("\n");
		return;
	}
	else if(upper_deck.size == ind_up)
	{
		new_deck.cards[i] = lower_deck.cards[ind_low];
		_recursion(upper_deck, lower_deck, new_deck, ind_low+1, ind_up, i+1);
		
	}
	else if(lower_deck.size == ind_low)
	{
		new_deck.cards[i] = upper_deck.cards[ind_up];
		_recursion(upper_deck, lower_deck, new_deck, ind_low, ind_up+1, i+1);
	}
	else
	{
		new_deck.cards[i] = upper_deck.cards[ind_up];
		_recursion(upper_deck, lower_deck, new_deck, ind_low, ind_up+1, i+1);
		new_deck.cards[i] = lower_deck.cards[ind_low];
		_recursion(upper_deck,lower_deck, new_deck, ind_low+1, ind_up, i+1);
	}

}

	


void interleave(CardDeck upper_deck, CardDeck lower_deck) {
	CardDeck new_deck = { .size = (upper_deck.size + lower_deck.size), .cards = {'0'} }; // definition of new card deck 
	int ind_low = 0;
	int ind_up = 0;
	int i = 0;
	_recursion( upper_deck, lower_deck, new_deck, ind_low, ind_up, i);
	
}

void shuffle(CardDeck orig_deck) {    
	int numpairs = orig_deck.size -1 ; // number of upper and lower deck pairs 
	int i = 0; // the index of upper_deck and lower_deck to call interleave 

	CardDeck * upper_deck = malloc(sizeof(*upper_deck)*numpairs);
	CardDeck * lower_deck = malloc(sizeof(*lower_deck)*numpairs);

	// allocate memory
	if (upper_deck == NULL || lower_deck == NULL) {
		free(upper_deck); 
		free(lower_deck); 
	}

	// call divideDeck to fill upper_deck and lower_deck 
	
	divide(orig_deck, upper_deck, lower_deck);

	while (i < numpairs) {
		// for each pairs call interleave
		interleave(upper_deck[i], lower_deck[i]);
		i++;
	}

	free(upper_deck);
	free(lower_deck);
} 
