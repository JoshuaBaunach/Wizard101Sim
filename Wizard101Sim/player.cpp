#include "player.h"
#include "constants.h"

#include <fstream>
#include <string>
#include <iostream>
#include <stack>
#include <vector>
// #include <time.h>
#include <random>

using namespace std;

Player::Player(int lv, int sch)
{
	level = lv;
	school = sch;
	set_hp_mana();
}

// Shuffle the deck of cards
void Player::shuffle()
{
	// Move both deck and discard pile into discard buffer
	while (!deck.empty())
	{
		shuffle_buffer.push_back(deck.top());
		deck.pop();
	}
	while (!discard.empty())
	{
		shuffle_buffer.push_back(discard.top());
		discard.pop();
	}

	// Apply Fisher-Yates shuffle algorithm to buffer vector
	for (int i = shuffle_buffer.size()-1; i > 0; i--)
	{
		//srand((unsigned int)time(NULL));
		int j = generate_random(0, i);
		Spell temp = shuffle_buffer[i];
		shuffle_buffer[i] = shuffle_buffer[j];
		shuffle_buffer[j] = temp;
	}

	// Push back into deck
	while (!shuffle_buffer.empty())
	{
		deck.push(shuffle_buffer[shuffle_buffer.size() - 1]);
		shuffle_buffer.pop_back();
	}
}

// Add a card to the deck
void Player::add_to_deck(Spell card)
{
	deck.push(card);
}

void Player::init_player()
{
	// Shuffle the deck
	shuffle();

	// Add the top seven cards of the hand to the deck if full, otherwise add whatever is in there
	if (deck.size() < 7)
	{
		while (!deck.empty())
		{
			hand.push_back(deck.top());
			deck.pop();
		}
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			hand.push_back(deck.top());
			deck.pop();
		}
	}
}

void Player::make_move()
{
	if (action == -1) // If the player is passing this round
		return;

	// Otherwise, the player is casting a spell
	// cast_spell(action, Player at action_target);
}

void Player::cast_spell(int index, Player* target)
{
	// Check whether the spell is cast via accuracy
	Spell to_cast = hand[index];
	vector<Spell_Effect> to_cast_effects = to_cast.get_effects();
	//srand((unsigned int)time(NULL));
	if (generate_random(0,100) > to_cast.get_accuracy()) // Cast failed
	{
		cout << "Cast failed" << endl;
		return;
	}

	// Cast is successful
	for (size_t i = 0; i < to_cast_effects.size(); i++)
	{
		int effect_type = to_cast_effects[i].get_type();
		vector<int> effect_values = to_cast_effects[i].get_values();
		switch (effect_type)
		{
		case 1: // Damage on single target
			// rerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorerorero
			// Do not ask what the above comment is. I was bored. I am leaving it in.
			vector<int> accuracies;
			accuracies.push_back(effect_values[effect_values[1]+2]);
			for (int i = 3 + effect_values[1]; i < 2 * effect_values[1] + 2; i++) accuracies.push_back(accuracies[accuracies.size()-1]+effect_values[i]);
			
			// Determine which damage value will be used
			//srand((unsigned int)time(NULL));
			int damage_acc_value = generate_random(1, 100);
			int damage_index = 0;
			for (size_t i = accuracies.size()-1; i < accuracies.size(); i--) // TIL size_t underflows once it goes negative
			{
				if (damage_acc_value <= accuracies[i]) damage_index = i;
			}

			// Calculate bonuses
			int damage_total = effect_values[2 + damage_index];

			target->take_damage(damage_total);
		}
	}
}

void Player::take_damage(int amount)
{
	// Calculate based on modifiers from this player
	int damage_total = amount;

	hp -= amount;
}

// Here's a bunch of getter functions. Enjoy
vector<Spell> Player::get_hand() { return hand; }
stack<Spell> Player::get_discard() { return discard; }
stack<Spell> Player::get_permanant_discard() { return permanant_discard; }
vector<Spell> Player::get_shuffle_buffer() { return shuffle_buffer; }
bool Player::get_is_ai() { return is_ai; }
int Player::get_level() { return level; }
int Player::get_max_hp() { return max_hp; }
int Player::get_hp() { return hp; }
int Player::get_max_mana() { return max_mana; }
int Player::get_mana() { return mana; }
int Player::get_school() { return school; }
int Player::get_action() { return action; }
int Player::get_action_target() { return action_target; }

void Player::set_hp_mana()
{
	// Parse the level table
	ifstream level_table(CONSTANTS::LEVEL_CHART_PATH);
	string line;

	for (int i = 1; i < level; i++) getline(level_table, line);
	for (int i = 1; i < school; i++) getline(level_table, line, '\t');

	getline(level_table, line, '\t'); // We should be at the desired position now
	hp = atoi(line.c_str());

	// Determine mana
	for (int i = school + 1; i < 8; i++) getline(level_table, line, '\t');
	getline(level_table, line, '\t');
	mana = atoi(line.c_str());

	max_hp = hp;
	max_mana = mana;
}

int Player::generate_random(int a, int b)
{
	random_device generator;
	uniform_int_distribution<int> distribution(a, b);
	return distribution(generator);
}
