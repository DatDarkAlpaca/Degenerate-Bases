#pragma once
#include "input.h"
#include "fasta.h"
#include "settings.h"

namespace permutator
{
	void execute();

	void insert_chunk(vector<string>&& chunkResults, size_t& chunksWritten, ofstream&& fastaOut);

	unsigned char lazy_cartesian(size_t j, size_t i);

	void lazy_preparation();

	void simple_base_insertion();

	void lazy_permutation();
}

