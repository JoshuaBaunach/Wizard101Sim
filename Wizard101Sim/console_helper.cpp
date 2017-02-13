#include "console_helper.h"

#include <iostream>
#include <string>

using namespace std;

/*
Clears the consle screen
(... hey, it works)
*/
void Console_Helper::clear_screen()
{
	cout << string(100, '\n');
}

/*
Reads an integer from stdin
*/
int Console_Helper::read_int()
{
	int to_return;
	string dummy;

	while (true)
	{
		cin >> to_return;

		if (cin.fail())
		{
			cin.clear();
			cin >> dummy;
			cin.ignore(256, '\n');
			cout << "Error: Invalid Input\n";
		}
		else
			return to_return;
	}
}