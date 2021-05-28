#include "pch.h"
#include "logger.h"
#include "menu.h"

bool RepeatOperation()
{
	string choice;
	getline(cin, choice);

	for (char& c : choice) 
		c = toupper(c);

	if (!choice.find("N") || !choice.find("NAO") || !choice.find("NO"))
		return false;
	else
		return true;
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

		input::retrieve_input();

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
