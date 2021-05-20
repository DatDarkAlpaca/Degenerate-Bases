#pragma once
#include "pch.h"
#include "unit.h"

namespace program_data
{
	// Size Methods:
	size_t get_lazy_cartesian_size();
	size_t get_input_size();

	// Helpers:
	bool any_degenerate_bases();
	void clear_permutator_data();

	// Units:
	extern vector<pair<int, Unit>> unitList;
	extern vector<char> allBases;

	// Unit Sizes:
	extern size_t doubles, triples, quadriples, normals, gaps;
	 
	// Chunk Size:
	extern size_t chunkSize;

	// Warning Sizes:
	const extern size_t warningCartesianSize;
	const extern size_t errorCartesianSize;

	// Execution Time:
	extern long long permutationTime, writeFastaTime;

	// Debug Variables:
	extern bool enableLogging, writeDebug, debug;

	// Result Variables:
	extern string initializationCharacter;
	extern string sequenceTemplate;
	extern string resultsFolder;
	extern string resultPrefix;
	extern string resultFormat;

	// Fasta Variable:
	extern size_t fastaIndex;

	// Log Variables:
	extern size_t iterations, outcomes;
	extern string logsFolder;
	extern string logPrefix;
	extern size_t logIndex;

	// Input Variable:
	extern string input;
}