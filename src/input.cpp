#include "pch.h"
#include "menu.h"
#include "input.h"

vector<char> allBases = {};

bool sanitized = false;

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
	vector<char> allBases = program_data::allBases;
	string input = program_data::input;

	input.erase(remove_if(input.begin(), input.end(), 
		[&allBases](char& c) {
			return !(std::find(allBases.begin(), allBases.end(), c) != allBases.end());
		}), input.end());

	if (program_data::input != input)
		cout << "[!] One of the bases inserted is not a degenerate base. Please check your sequence for precise outcomes.\n";

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
			switch (a.first)
			{
				case 4: {
					if (i == a.second.GetDegenerateBase())
						program_data::quadriples++;
					break;
				}
				case 3: {
					if (i == a.second.GetDegenerateBase())
						program_data::triples++;
					break;
				}
				case 2: {
					if (i == a.second.GetDegenerateBase())
						program_data::doubles++;
					break;
				}
				case 1: {
					if (i == a.second.GetDegenerateBase())
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
