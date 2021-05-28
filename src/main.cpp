#include "pch.h"
#include "logger.h"
#include "menu.h"

bool repeat_operation()
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

bool parse_commands()
{
	auto to_lower = [](string& str) { for (char& c : str) c = std::tolower(c); return str; };

	if (to_lower(program_data::input) == "help")
	{
		menu::help_menu();
		return true;
	}
	else if (to_lower(program_data::input) == "bases" || to_lower(program_data::input) == "base")
	{
		menu::base_list();
		return true;
	}
	else return false;
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	settings::load();
	logger::load();
	fasta::load();

	while (true)
	{
		menu::header();
		menu::show_information();

		menu::get_input();

		input::retrieve_input();

		if (parse_commands())
			continue;

		input::sanitize_input();

		permutator::execute();

		menu::debug_info();

		logger::log_data();

		menu::post_execution();

		program_data::clear_permutator_data();

		if (!repeat_operation())
			break;
	}
	
	menu::finalize();
	
	cin.get();
	return 0;
}
