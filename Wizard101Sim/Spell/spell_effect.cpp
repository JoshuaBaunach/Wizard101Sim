#include "spell_effect.h"

#include <vector>

using namespace std;

Spell_Effect::Spell_Effect(int spell_type)
{
	type = spell_type;
}

void Spell_Effect::add_value(int val)
{
	values.push_back(val);
}

vector<int> Spell_Effect::get_values()
{
	return values;
}

int Spell_Effect::get_type()
{
	return type;
}
