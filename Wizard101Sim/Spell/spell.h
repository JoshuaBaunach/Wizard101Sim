#pragma once

#include "spell_effect.h"
#include <string>
#include <vector>

using namespace std;

class Spell
{
public:
	// Constructor
	Spell(int spell_id, const char* spell_name, const char* spell_description, int spell_school, int spell_accuracy, int spell_pips, int spell_type, bool spell_shadow);

	// Copy constructor
	Spell(Spell* other);

	// = Operator
	Spell& operator=(const Spell other);

	// Prints the details of the spell
	void print_details();

	// Prints the effects of the spell
	void print_effects();

	// Sets the effect(s) of the spell
	void set_effects(vector<Spell_Effect> spell_effects);

	// A bunch of getters
	string get_name();
	string get_description();
	int get_school();
	int get_accuracy();
	int get_pips();
	int get_type();
	int get_id();
	bool get_shadow();
	vector<Spell_Effect> get_effects();

private:
	string name, description;
	int school, accuracy, pips, type, id;
	bool shadow;
	vector<Spell_Effect> effects;
};