#include "pch.h"
#include "data.h"

namespace program_data
{
	// Units:
	vector<pair<int, Unit>> unitList = {
		{ 4, Unit('N', {'A', 'C', 'T', 'G'}) },

		{ 3, Unit('D', {'A', 'G', 'T'}) },
		{ 3, Unit('V', {'A', 'C', 'G'}) },
		{ 3, Unit('B', {'C', 'G', 'T'}) },
		{ 3, Unit('H', {'A', 'C', 'T'}) },

		{ 2, Unit('W', {'A', 'T'}) },
		{ 2, Unit('S', {'C', 'G'}) },
		{ 2, Unit('K', {'G', 'T'}) },
		{ 2, Unit('M', {'A', 'C'}) },
		{ 2, Unit('Y', {'C', 'T'}) },
		{ 2, Unit('R', {'A', 'G'}) },

		{ 1, Unit('A', {'A'}) },
		{ 1, Unit('C', {'C'}) },
		{ 1, Unit('G', {'G'}) },
		{ 1, Unit('T', {'T'}) },

		{ 1, Unit('.', {'.'}) },
		{ 1, Unit('-', {'-'}) },
	};
	vector<char> allBases = {
		'N', 'D', 'V', 'B', 'H',
		'W', 'S', 'K', 'M', 'Y',
		'R', 'A', 'C', 'G', 'T',
		'.', '-' };

	// Unit Sizes:
	size_t doubles, triples, quadriples, normals, gaps;

	// Chunk Size:
	size_t chunkSize;

	// Warning Sizes:
	const size_t warningCartesianSize = 16777216;
	const size_t errorCartesianSize = 268435456;

	// Execution Time:
	long long permutationTime, writeFastaTime;

	// Debug Variables:
	bool enableLogging, writeDebug, debug;
	
	// Result Variables:
	string initializationCharacter;
	string sequenceTemplate;
	string resultsFolder;
	string resultPrefix;
	string resultFormat;

	// Fasta Variable:
	size_t fastaIndex;
	
	// Log Variables:
	size_t iterations, outcomes;
	string logsFolder;
	string logPrefix;
	size_t logIndex;

	// Input Variable:
	string input = "";
}

// Size Methods:
size_t program_data::get_lazy_cartesian_size() 
{
	size_t size = 1;

	if (quadriples > 0) size *= (size_t)pow(4, quadriples);
	if (triples > 0)	size *= (size_t)pow(3, triples);
	if (doubles > 0)	size *= (size_t)pow(2, doubles);

	return size;
}

size_t program_data::get_input_size()
{
	return input.size();
}

// Helpers:
bool program_data::any_degenerate_bases() 
{
	return (quadriples > 0 || triples > 0 || doubles > 0);
}

void program_data::clear_permutator_data()
{
	doubles = 0;
	triples = 0;
	quadriples = 0;
	normals = 0;
	gaps = 0;

	program_data::outcomes = 0;
	program_data::iterations = 0;

	program_data::permutationTime = 0;
	program_data::writeFastaTime = 0;
}
