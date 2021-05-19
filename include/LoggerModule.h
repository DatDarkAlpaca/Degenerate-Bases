#pragma once
#include "Data.h"

namespace logger
{
	void load();

	void log_data();

	bool exists_log_folder();

	void create_default();

	void check_last_fileName();
}