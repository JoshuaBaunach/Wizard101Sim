#include "combat_instance.h"

Combat_Instance::Combat_Instance()
{
	turn_count = 1;
}

void Combat_Instance::set_team_1(vector<Player*> team)
{
	team_1 = team;
}

void Combat_Instance::set_team_2(vector<Player*> team)
{
	team_2 = team;
}

void Combat_Instance::init_combat_instance()
{
	// Initialize each of the players on each team
	for (size_t i = 0; i < team_1.size(); i++) team_1[i]->init_player();
	for (size_t i = 0; i < team_2.size(); i++) team_2[i]->init_player();

	get_moves(team_1, team_2);
	get_moves(team_2, team_1);
	run_turn();
}

void Combat_Instance::run_turn()
{
	// Run all of the actions of team 1
	for (size_t i = 0; i < team_1.size(); i++)
	{
		if (team_1[i]->get_hp() > 0) // If the player is alive
			team_1[i]->make_move();
	}

	// Run all of the actions of team 2
	for (size_t i = 0; i < team_2.size(); i++)
	{
		if (team_2[i]->get_hp() > 0) // If the player is alive
			team_2[i]->make_move();
	}

	// Determine if there is a winner yet
	int team_1_total_hp = 0;
	int team_2_total_hp = 0;
	for (size_t i = 0; i < team_1.size(); i++) team_1_total_hp += team_1[i]->get_hp();
	for (size_t i = 0; i < team_2.size(); i++) team_2_total_hp += team_2[i]->get_hp();

	if (team_1_total_hp <= 0 && team_2_total_hp <= 0)
	{
		cout << "Tie!" << endl;
		return;
	}
	else if (team_1_total_hp <= 0)
	{
		cout << "Team 2 wins!" << endl;
		return;
	}
	else if (team_2_total_hp <= 0)
	{
		cout << "Team 1 wins!" << endl;
		return;
	}

	// If there is not a winner, move on to next round
	turn_count++;
	get_moves(team_1, team_2);
	get_moves(team_2, team_1);
	run_turn();
}

void Combat_Instance::get_moves(vector<Player*> team, vector<Player*> opposing)
{
	// Print a menu for each players' actions, assuming the player isn't an AI
	for (size_t i = 0; i < team.size(); i++)
	{
		if (!team[i]->get_is_ai())
		{
			vector<Spell> player_hand = team[i]->get_hand();
			Menu choice_menu;
			choice_menu.set_title("Action for Player " + to_string(i+1));
			choice_menu.set_blurb("Choose an action for player " + to_string(i+1) + " to perform");
			
			// Give the player all his/her options
			for (size_t j = 0; j < player_hand.size(); j++)
			{
				// Split into multiple lines so it does not look ugly
				string name_and_description = player_hand[j].get_name() + ". " + player_hand[j].get_description();
				string details = " (" + CONSTANTS::SCHOOL_NAMES[player_hand[j].get_school()] + ", " + to_string(player_hand[j].get_accuracy()) + "%)";
				choice_menu.add_option(name_and_description + details);
			}
			choice_menu.add_option("Pass");
			// TODO: Give player option to get treasure card

			int option = choice_menu.disp_menu();
			
			if (option != player_hand.size() + 1) // If the player did not pass
			{
				int target_type = 1; // 0 = No target, 1 = Single enemy, 2 = Single ally
				// Determine whether the player must select a target based on spell.
				Spell selected_spell = player_hand[option - 1];
				switch (selected_spell.get_type())
				{
				case 1: // Single target damage
					target_type = 1;
					break;
				}

				// Determine target
				if (target_type == 1) // Select opposing target (with option to go back)
				{
					choice_menu.set_title("Select target");
					choice_menu.set_blurb("Select the target for the spell:");
					choice_menu.remove_all_options();
					for (size_t j = 0; j < opposing.size(); j++) choice_menu.add_option("Opposing Player " + to_string(j + 1));
					choice_menu.add_option("Back");
					int target_option = choice_menu.disp_menu();

					if (target_option != opposing.size() + 1) // If the player is not passing
					{
						team[i]->set_action(option - 1);
						team[i]->set_action_target(opposing[target_option-1]);
					}

					else // Go back
					{
						i--;
					}
				}
			}
		}
	}
}
