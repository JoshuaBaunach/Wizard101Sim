#include "player.h"
#include "spell_file_parser.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	// Get the file
	string file_path,file_path_multiple;
	file_path = "C:\\Users\\Joshua Baunach\\Documents\\Wizard101Sim\\spells\\single_spell.json";
	file_path_multiple = "C:\\Users\\Joshua Baunach\\Documents\\Wizard101Sim\\spells\\multiple_spells.json";

	// Let's parse this thing
	Spell_File_Parser parser(file_path);
	Spell_File_Parser parser_multiple(file_path_multiple);
	Spell test_spell = parser.parse_spell();
	vector<Spell> test_spells = parser_multiple.parse_spell_vector();

	Player player1(120, 1);
	Player player2(120, 2);
	player1.add_to_deck(test_spell);
	player1.init_player();
	player2.init_player();

	cout << "Player 2 HP before: " << player2.get_hp() << endl;

	player1.cast_spell(0, &player2);

	cout << "Player 2 HP after: " << player2.get_hp() << endl;

	system("PAUSE"); // Using system smh
	return 0;
}