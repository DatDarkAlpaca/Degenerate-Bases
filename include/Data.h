#pragma once
#include "pch.h"
#include "unit.h"

namespace program_data
{
	size_t get_lazy_cartesian_size();

	size_t get_input_size();

	bool any_degenerate_bases();

	void clear_permutator_data();

	extern size_t doubles, triples, quadriples, normals, gaps;
	extern size_t iterations, outcomes;
	 
	extern size_t fastaIndex, logIndex;
	extern size_t chunkSize;

	extern size_t warningCartesianSize;
	extern size_t errorCartesianSize;

	extern vector<pair<int, Unit>> unitList;
	extern vector<char> allBases;

	extern long long permutationTime, writeFastaTime;

	extern bool enableLogging, writeDebug, debug;

	extern string initializationCharacter;
	extern string sequenceTemplate;

	extern string resultPrefix;
	extern string logPrefix;

	extern string resultFormat;

	extern string resultsFolder;
	extern string logsFolder;

	extern string input;
}