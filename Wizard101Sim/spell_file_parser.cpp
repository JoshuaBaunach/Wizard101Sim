#include "spell_file_parser.h"

Spell_File_Parser::Spell_File_Parser(string sp_file)
{
	// Open and read the file into a string (then convert into c string)
	ifstream json_file(sp_file);
	string json_string, line;

	if (!json_file.is_open())
	{
		cout << "Invalid file" << endl;
		return;
	}

	while (getline(json_file, line))
		json_string += line;

	json_file.close();

	const char* json = json_string.c_str();

	doc.Parse(json);
}

// Parse a single spell from the file
Spell Spell_File_Parser::parse_spell()
{
	int id = doc["id"].GetInt();
	string name = doc["name"].GetString();
	string description = doc["description"].GetString();
	int school = doc["school"].GetInt();
	int accuracy = doc["accuracy"].GetInt();
	int pips = doc["pips"].GetInt();
	int type = doc["type"].GetInt();
	bool shadow = doc["shadow"].GetBool();

	vector<Spell_Effect> spell_effects;

	Value effects = doc["effects"].GetArray();
	for (Value::ValueIterator i = effects.Begin(); i != effects.End(); i++)
	{
		// Each value of i should be an object
		Value effect = i->GetObject();
		Value::MemberIterator effect_iterator = effect.MemberBegin();
		int effect_type = effect[effect_iterator->name.GetString()].GetInt();
		Spell_Effect new_effect(effect_type);
		effect_iterator++;

		Value effect_values = effect[effect_iterator->name.GetString()].GetArray();
		for (Value::ValueIterator values_iterator = effect_values.Begin(); values_iterator != effect_values.End(); values_iterator++)
			new_effect.add_value(values_iterator->GetInt());

		spell_effects.push_back(new_effect);
	}

	Spell parsed_spell(id, name.c_str(), description.c_str(), school, accuracy, pips, type, shadow);
	parsed_spell.set_effects(spell_effects);

	return parsed_spell;
}

vector<Spell> Spell_File_Parser::parse_spell_vector()
{
	vector<Spell> to_return;

	Value spells = doc["spells"].GetArray();

	// Iterate through the array
	for (Value::ValueIterator spells_iterator = spells.Begin(); spells_iterator != spells.End(); spells_iterator++)
	{
		Value spell = spells_iterator->GetObject();

		// Mostly copypasted code from parse_spell below. If you fix something here, don't forget to fix above
		Value::MemberIterator spell_iterator = spell.MemberBegin();
		int id = spell[spell_iterator->name.GetString()].GetInt();
		spell_iterator++;
		string name = spell[spell_iterator->name.GetString()].GetString();
		spell_iterator++;
		string description = spell[spell_iterator->name.GetString()].GetString();
		spell_iterator++;
		int school = spell[spell_iterator->name.GetString()].GetInt();
		spell_iterator++;
		int accuracy = spell[spell_iterator->name.GetString()].GetInt();
		spell_iterator++;
		int pips = spell[spell_iterator->name.GetString()].GetInt();
		spell_iterator++;
		int type = spell[spell_iterator->name.GetString()].GetInt();
		spell_iterator++;
		bool shadow = spell[spell_iterator->name.GetString()].GetBool();
		spell_iterator++;

		vector<Spell_Effect> spell_effects;

		Value effects = spell[spell_iterator->name.GetString()].GetArray();

		for (Value::ValueIterator i = effects.Begin(); i != effects.End(); i++)
		{
			// Each value of i should be an object
			Value effect = i->GetObject();
			Value::MemberIterator effect_iterator = effect.MemberBegin();
			int effect_type = effect[effect_iterator->name.GetString()].GetInt();
			Spell_Effect new_effect(effect_type);
			effect_iterator++;

			Value effect_values = effect[effect_iterator->name.GetString()].GetArray();
			for (Value::ValueIterator values_iterator = effect_values.Begin(); values_iterator != effect_values.End(); values_iterator++)
				new_effect.add_value(values_iterator->GetInt());

			spell_effects.push_back(new_effect);
		}

		Spell parsed_spell(id, name.c_str(), description.c_str(), school, accuracy, pips, type, shadow);
		parsed_spell.set_effects(spell_effects);

		to_return.push_back(parsed_spell);
	}

	return to_return;
}