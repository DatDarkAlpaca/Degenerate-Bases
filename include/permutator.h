#pragma once
#include "input.h"
#include "fasta.h"
#include "settings.h"

namespace permutator
{
	extern vector<vector<unsigned char>> sets;

	extern vector<size_t> moduli;

	extern vector<int> divisions;

	extern vector<unsigned char> cartesianResults;

	extern size_t maxSetSize;

	void execute();

	void insert_chunk(vector<string>&& chunkResults, size_t& chunksWritten, ofstream&& fastaOut);

	unsigned char lazy_cartesian(size_t j, size_t i);

	void lazy_preparation();

	void simple_base_insertion();

	void lazy_permutation();
}

