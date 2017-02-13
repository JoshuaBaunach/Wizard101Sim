#include "menu.h"
#include "console_helper.h"
#include <iostream>
#include <string>

using namespace std;

// Default constructor
Menu::Menu()
{
	title = "Default title";
	blurb = "Default blurb";
}

// == Operator (compares title and blurb)
bool Menu::operator==(const Menu other)
{
	return (title == other.title && blurb == other.blurb);
}

// Sets title
void Menu::set_title(string t)
{
	title = t;
}

// Sets blurb
void Menu::set_blurb(string b)
{
	blurb = b;
}

// Adds a Menu to the end of the vector of options.
void Menu::add_option(string option)
{
	options.push_back(option);
}

// Removes a Menu from the vector of options. Returns true if removed successfully, false if otherwise
bool Menu::remove_option(string option)
{
	for (vector<string>::iterator iter = options.begin(); iter != options.end(); iter++)
	{
		if (*iter == option)
		{
			options.erase(iter);
			return true;
		}
	}
	return false;
}

// Removes all options
void Menu::remove_all_options()
{
	while (!options.empty())
		options.pop_back();
}

// Prints the Menu
int Menu::disp_menu()
{
	int user_response;

	Console_Helper::clear_screen();

	// Print the title in a fancy box
	cout << "====";
	for (size_t i = 0; i < title.length(); i++) cout << "=";
	cout << "====" << endl;
	cout << "|   ";
	for (size_t i = 0; i < title.length(); i++) cout << " ";
	cout << "   |" << endl;
	cout << "|   " << title << "   |" << endl;
	cout << "|   ";
	for (size_t i = 0; i < title.length(); i++) cout << " ";
	cout << "   |" << endl;
	cout << "====";
	for (size_t i = 0; i < title.length(); i++) cout << "=";
	cout << "====" << endl;
	cout << blurb << endl;

	// Print the options
	for (size_t i = 0; i < options.size(); i++) cout << (i + 1) << ". " << options[i] << endl;

	// Get some input from the user
	do
	{
		user_response = Console_Helper::read_int();
	} while ((user_response < 1) || (user_response > (int)options.size()));
	
	return user_response;
}
