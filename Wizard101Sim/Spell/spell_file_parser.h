#pragma once

#include "spell.h"
#include "spell_effect.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
using namespace rapidjson;

class Spell_File_Parser
{
public:
	// Construct the class
	Spell_File_Parser(string sp_file);

	// Parse a single spell from the file
	Spell parse_spell();

	// Parse all spells from the file
	vector<Spell> parse_spell_vector();
private:
	string file;
	Document doc;
};