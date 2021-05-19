#pragma once
#include "Settings.h"
#include "InputModule.h"
#include "PermutatorModule.h"

namespace menu
{
	void get_input();

	void debug_info();

	void post_execution();

	void finalize();

	void write_chunk_size();

	void write_chunk(size_t chunk);

	void unmatched_bases_errors();

	void cartesian_size_warning();
}
