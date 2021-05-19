#include "pch.h"
#include "Data.h"

namespace program_data
{
	size_t warningCartesianSize = 16777216;
	size_t errorCartesianSize = 268435456;

	size_t doubles, triples, quadriples, normals, gaps;
	size_t iterations, outcomes;

	size_t fastaIndex, logIndex;
	size_t chunkSize;

	vector<pair<int, Unit>> unitList = {};
	vector<char> allBases;

	long long permutationTime, writeFastaTime;

	bool enableLogging, writeDebug, debug;

	string initializationCharacter;
	string sequenceTemplate;

	string resultPrefix;
	string logPrefix;

	string resultFormat;

	string resultsFolder;
	string logsFolder;

	string input = "";
}

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
