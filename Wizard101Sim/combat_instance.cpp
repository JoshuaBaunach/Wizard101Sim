#include "combat_instance.h"

Combat_Instance::Combat_Instance()
{
	turn_count = 1;
}

void Combat_Instance::set_team_1(vector<Player> team)
{
	team_1 = team;
}

void Combat_Instance::set_team_2(vector<Player> team)
{
	team_2 = team;
}

void Combat_Instance::init_combat_instance()
{
	// Initialize each of the players on each team
	for (int i = 0; i < team_1.size(); i++) team_1[i].init_player();
	for (int i = 0; i < team_2.size(); i++) team_2[i].init_player();
}
