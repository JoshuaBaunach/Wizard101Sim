#pragma once

#include "player.h"
#include <vector>

class Combat_Instance
{
public:
	// Default Constructor
	Combat_Instance();

	// Sets the first and second team
	void set_team_1(vector<Player> team);
	void set_team_2(vector<Player> team);

	// Initializes combat instance (assumes both teams have been set
	void init_combat_instance();

	// Runs the turn of the battle
	void run_turn();

private:
	vector<Player> team_1;
	vector<Player> team_2;
	int turn_count;
};