#pragma once

#include <vector>

using namespace std;

class Spell_Effect
{
public:
	// Constructor (takes in integer for type and input stream for spell values)
	Spell_Effect(int spell_type);

	// Add an effect value to the end of the values list
	void add_value(int val);

	// Gets the values of the spell effect
	vector<int> get_values();

	// Gets the type of the spell effect
	int get_type();
private:
	int type;
	vector<int> values;
};