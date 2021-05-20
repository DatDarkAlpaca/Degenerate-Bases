#include "pch.h"
#include "logger.h"
#include "menu.h"

string RetrieveInput()
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

	return input;
}

bool RepeatOperation()
{
	string choice;
	getline(cin, choice);

	for (char& c : choice) c = toupper(c);

	if (!choice.find("N") || !choice.find("NAO") || !choice.find("NO"))
		return false;
	else
	{
		//system("cls");
		return true;
	}	
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	settings::load();
	logger::load();	
	fasta::load();

	while (true)
	{
		menu::get_input();

		program_data::input = RetrieveInput();

		input::sanitize_input();

		permutator::execute();

		menu::debug_info();

		logger::log_data();

		menu::post_execution();

		program_data::clear_permutator_data();

		if (!RepeatOperation())
			break;
	}
	
	menu::finalize();
	
	cin.get();
	return 0;
}
