#include "spell.h"
#include "constants.h"

#include <iostream>
#include <vector>

using namespace std;

// Constructor
Spell::Spell(int spell_id, const char* spell_name, const char* spell_description, int spell_school, int spell_accuracy, int spell_pips, int spell_type, bool spell_shadow)
{
	id = spell_id;
	name = spell_name;
	description = spell_description;
	school = spell_school;
	accuracy = spell_accuracy;
	pips = spell_pips;
	type = spell_type;
	shadow = spell_shadow;
}

Spell::Spell(Spell * other)
{
	// Copy pretty much everything here
	name = other->name;
	description = other->description;
	school = other->school;
	accuracy = other->accuracy;
	pips = other->pips;
	type = other->type;
	id = other->id;
	shadow = other->shadow;
	effects = other->effects;
}

Spell & Spell::operator=(const Spell other)
{
	// Copy pretty much everything here
	name = other.name;
	description = other.description;
	school = other.school;
	accuracy = other.accuracy;
	pips = other.pips;
	type = other.type;
	id = other.id;
	shadow = other.shadow;
	effects = other.effects;

	return *this;
}

void Spell::set_effects(vector<Spell_Effect> spell_effects)
{
	effects = spell_effects;
}

// A bunch of getters
string Spell::get_name() { return name; }
string Spell::get_description() { return description; }
int Spell::get_school() { return school; }
int Spell::get_accuracy() { return accuracy; }
int Spell::get_pips() { return pips; }
int Spell::get_type() { return type; }
int Spell::get_id() { return id; }
bool Spell::get_shadow() { return shadow; }
vector<Spell_Effect> Spell::get_effects() { return effects; }

void Spell::print_details()
{
	cout << name << " (";
	cout << CONSTANTS::SCHOOL_NAMES[school] << ", ";
	cout << accuracy << "% accuracy" << ", ";
	cout << pips << " pips" << ", ";
	cout << "Type: " << type << ")" << endl;
	cout << description << endl;
}

// Prints the details of a spell (mainly used for debugging)
void Spell::print_effects()
{
	for (size_t i = 0; i < effects.size(); i++)
	{
		vector<int> current_values = effects[i].get_values();
		switch (effects[i].get_type())
		{
		case 1: // Damage effect
			for (int i = 2; i < current_values[1] + 2; i++) cout << current_values[i] << "/";
			cout << " " << CONSTANTS::SCHOOL_NAMES[current_values[0]] << " damage to single enemy" << endl;
			break;
		}
	}
}
