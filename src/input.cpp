#include "pch.h"
#include "menu.h"
#include "input.h"

static bool sanitized = false;

void input::retrieve_input()
{
	string input;
	while (true)
	{
		getline(cin, input);

		if (input.length() >= 80)
		{
			cout << "[!] The sequence is longer than 80 bases. This might take a while." << '\n';
			cin.clear();
			break;
		}

		if (input.empty())
		{
			cout << "The sequence is empty. Please try again." << '\n';
			cin.clear();
			cout << '\n';
			menu::get_input();
			continue;
		}
		else break;
	}

	program_data::input = input;
}

void input::sanitize_input()
{
	capitalize();
	purge_excess();
	count_bases();
	get_cartesian_size();
}

void input::capitalize()
{
	for (char& i : program_data::input)
		i = toupper(i);
}

void input::purge_excess()
{
	const vector<char> allBases = { 'N', 'D', 'V', 'B', 'H', 'W', 'S', 'K', 'M', 'Y',
							        'R', 'A', 'C', 'G', 'T', '.', '-' };

	string input = program_data::input;

	input.erase(remove_if(input.begin(), input.end(), [&allBases](char& c) {
			return !(std::find(allBases.begin(), allBases.end(), c) != allBases.end());
		}), input.end());

	if (program_data::input != input)
		cout << "[!] One of the bases from the sequence is not a degenerate base. Please check your sequence for precise outcomes.\n";

	program_data::input = input;

	sanitized = true;
}

void input::count_bases()
{
	if (!sanitized)
		return;

	for (const char& i : program_data::input)
	{
		for (auto& a : program_data::unitList)
		{
			switch (a.possibleBasesSize)
			{
				case 4: {
					if (i == a.degenerateBase)
						program_data::quadriples++;
					break;
				}
				case 3: {
					if (i == a.degenerateBase)
						program_data::triples++;
					break;
				}
				case 2: {
					if (i == a.degenerateBase)
						program_data::doubles++;
					break;
				}
				case 1: {
					if (i == a.degenerateBase)
					{
						if (i != '.' && i != '-')
							program_data::normals++;
						else
							program_data::gaps++;
					}
					break;
				}
			}
		}
	}
}

void input::get_cartesian_size()
{
	if (program_data::get_lazy_cartesian_size() >= program_data::warningCartesianSize)
		menu::cartesian_size_warning();
}
