#pragma once
#include "unit.h"

namespace unit
{
	void load();

	vector<pair<char, vector<char>>> parse_units();

	bool check_translations();

	void create_default_translations();

	void insert_units();
}

