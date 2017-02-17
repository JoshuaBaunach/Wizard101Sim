#pragma once

#include "../../Wizard101Sim/Player/player.h"
#include "../../Wizard101Sim/Menu/menu.h"
#include "../../Wizard101Sim/Helpers/constants.h"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Combat_Instance
{
public:
	// Default Constructor
	Combat_Instance();

	// Sets the first and second team
	void set_team_1(vector<Player*> team);
	void set_team_2(vector<Player*> team);

	// Initializes combat instance (assumes both teams have been set
	void init_combat_instance();

	// Runs the turn of the battle
	void run_turn();

	// Gets the move of each player
	void get_moves(vector<Player*> team, vector<Player*> opposing);

	// 

private:
	vector<Player*> team_1;
	vector<Player*> team_2;
	int turn_count;
};