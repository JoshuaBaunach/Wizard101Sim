#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Menu
{
public:
	// Constructor
	Menu();

	// Operators
	bool operator==(const Menu other);

	// Setters
	void set_title(string t);
	void set_blurb(string b);
	
	// Other Functions
	// Adds a menu to the end of the vector of options.
	void add_option(string option);

	// Removes a menu from the vector of options. Returns true if removed successfully, false if otherwise
	bool remove_option(string option);

	// Removes all options
	void remove_all_options();

	// Prints the menu
	int disp_menu();

private:
	string title;
	string blurb;
	vector<string> options;
};