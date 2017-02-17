#pragma once

#include "spell.h"

#include <stack>
#include <vector>

class Player
{
public:
	// Constructor with level and school (is_ai will be false)
	Player(int lv, int sch);

	// Constructor with level, school, and AI type (is_ai will be true)
	// Player(int lv, int sch, int ai_id)

	// Shuffle the deck of cards
	void shuffle();
	
	// Add a card (or cards) to the deck
	void add_to_deck(Spell card);
	void add_to_deck(vector<Spell> card);

	// Initialize the player for the beginning of a game
	void init_player();

	// Sets the action to be done by the player and the action target
	void set_action(int act);
	void set_action_target(Player* act_target);

	// Called by a combat instance. Determines the move the player will make during that particular round.
	void make_move();

	// Called when the player casts a spell
	void cast_spell(int index, Player* target);

	// Called when the player takes damage
	void take_damage(int amount);

	// Getters
	vector<Spell> get_hand();
	stack<Spell> get_discard();
	stack<Spell> get_permanant_discard();
	vector<Spell> get_shuffle_buffer();
	Player* get_action_target();
	bool get_is_ai();
	int get_level();
	int get_max_hp();
	int get_hp();
	int get_max_mana();
	int get_mana();
	int get_school();
	int get_action();

private:
	int level, max_hp, hp, max_mana, mana, school, action;
	bool is_ai;
	stack<Spell> deck; // Deck of non-drawn cards
	stack<Spell> discard; // Discard pile; may be reshuffled back into deck
	stack<Spell> permanant_discard; // Discard stack for treasure cards and reshuffle cards
	vector<Spell> shuffle_buffer; // Buffer vector that will be shuffled and pushed back into deck
	vector<Spell> hand; // Current hand
	Player* action_target;

	// Determine HP and Mana from level table
	void set_hp_mana();

	// Generates a random number from a to b, inclusive
	int generate_random(int a, int b);
	// TODO: Incorporate treasure cards
};