#include "../Wizard101Sim/Spell/spell_file_parser.h"
#include "../Wizard101Sim/Combat/combat_instance.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	// Get the file
	string file_path,file_path_multiple;
	file_path = "single_spell.json";
	file_path_multiple = "multiple_spells.json";

	// Let's parse this thing
	Spell_File_Parser parser(file_path);
	Spell_File_Parser parser_multiple(file_path_multiple);
	Spell test_spell = parser.parse_spell();
	vector<Spell> test_spells = parser_multiple.parse_spell_vector();

	Player player1(1, 1);
	Player player2(1, 2);
	for (int i = 0; i < 3; i++) player1.add_to_deck(test_spell);
	for (int i = 0; i < 3; i++) player1.add_to_deck(test_spells);
	for (int i = 0; i < 3; i++) player2.add_to_deck(test_spell);
	for (int i = 0; i < 3; i++) player2.add_to_deck(test_spells);
	
	Combat_Instance instance;
	vector<Player*> team1, team2;
	team1.push_back(&player1);
	team2.push_back(&player2);
	instance.set_team_1(team1);
	instance.set_team_2(team2);
	instance.init_combat_instance();
	/*
	player1.init_player();
	player2.init_player();

	cout << "Player 2 HP before: " << player2.get_hp() << endl;
	cout << "Casting " << test_spells[1].get_name() << endl;

	player1.cast_spell(0, &player2);

	cout << "Player 2 HP after: " << player2.get_hp() << endl;
	*/

	system("PAUSE"); // Using system smh
	return 0;
}