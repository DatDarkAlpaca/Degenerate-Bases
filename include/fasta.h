#pragma once
#include "settings.h"

namespace fasta
{
	void load();

	void write_vector(vector<string>&& results, ofstream&& mFastaFile);

	void write_result(string&& result, ofstream&& mFastaFile);

	void open_file(ofstream&& mFastaFile);

	void close_file(ofstream&& mFastaFile);

	bool exists_results_folder();

	void create_results_folder();

	void check_last_filename();
}