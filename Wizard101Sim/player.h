#pragma once

#include "spell.h"

#include <stack>
#include <vector>

class Player
{
public:
	// Constructor with level and school
	Player(int lv, int sch);

	// Shuffle the deck of cards
	void shuffle();
	
	// Add a card to the deck
	void add_to_deck(Spell card);

	// Initialize the player for the beginning of a game
	void init_player();


	// Getters
	vector<Spell> get_hand();
private:
	int level, hp, mana, school;
	stack<Spell> deck; // Deck of non-drawn cards
	stack<Spell> discard; // Discard pile; may be reshuffled back into deck
	stack<Spell> permanant_discard; // Discard stack for treasure cards and reshuffle cards
	vector<Spell> shuffle_buffer; // Buffer vector that will be shuffled and pushed back into deck
	vector<Spell> hand; // Current hand

	// Determine HP and Mana from level table
	void set_hp_mana();

	// TODO: Incorporate treasure cards
};