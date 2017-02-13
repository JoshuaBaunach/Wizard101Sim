#include "player.h"
#include "spell_file_parser.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	Player play(120, 7);

	// Get the file
	string file_path,file_path_multiple;
	file_path = "C:\\Users\\Joshua Baunach\\Documents\\Wizard101Sim\\spells\\single_spell.json";
	file_path_multiple = "C:\\Users\\Joshua Baunach\\Documents\\Wizard101Sim\\spells\\multiple_spells.json";

	// Let's parse this thing
	Spell_File_Parser parser(file_path);
	Spell_File_Parser parser_multiple(file_path_multiple);
	Spell test_spell = parser.parse_spell();
	vector<Spell> test_spells = parser_multiple.parse_spell_vector();

	test_spell.print_details();
	for (size_t i = 0; i < test_spells.size(); i++) test_spells[i].print_details();

	system("PAUSE"); // Using system smh
	return 0;
}