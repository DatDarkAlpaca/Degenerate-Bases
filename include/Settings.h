#pragma once
#include "pch.h"

namespace settings
{
	void load();

	bool exists_settings();

	void create_default();

	void retrieve();

	void parse();
}
