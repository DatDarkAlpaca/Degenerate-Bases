#include "pch.h"
#include "data.h"

namespace program_data
{
	// Units:
	vector<Unit> unitList = { 
		Unit('N', {'A', 'C', 'T', 'G'}),

		Unit('D', {'A', 'G', 'T'}),
		Unit('V', {'A', 'C', 'G'}),
		Unit('B', {'C', 'G', 'T'}),
		Unit('H', {'A', 'C', 'T'}),

		Unit('W', {'A', 'T'}),
		Unit('S', {'C', 'G'}),
		Unit('K', {'G', 'T'}),
		Unit('M', {'A', 'C'}),
		Unit('Y', {'C', 'T'}),
		Unit('R', {'A', 'G'}),

		Unit('A', {'A'}),
		Unit('C', {'C'}),
		Unit('G', {'G'}),
		Unit('T', {'T'}),

		Unit('.', {'.'}),
		Unit('-', {'-'})
	};

	// Unit Sizes:
	size_t doubles, triples, quadriples, normals, gaps;

	// Chunk Size:
	size_t chunkSize;

	// Warning Size:
	const size_t warningCartesianSize = 16777216;

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

// Size Method?
size_t program_data::get_lazy_cartesian_size() 
{
	size_t size = 1;

	if (quadriples > 0) size *= (size_t)pow(4, quadriples);
	if (triples > 0)	size *= (size_t)pow(3, triples);
	if (doubles > 0)	size *= (size_t)pow(2, doubles);

	return size;
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
