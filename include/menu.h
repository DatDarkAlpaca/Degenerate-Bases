#pragma once
#include "settings.h"
#include "input.h"
#include "permutator.h"

namespace menu
{
	void header();
	
	void show_information();

	void help_menu();

	void base_list();

	void get_input();

	void debug_info();

	void post_execution();

	void finalize();

	void write_chunk_size();

	void write_chunk(size_t chunk);

	void unmatched_bases_errors();

	void cartesian_size_warning();
}
