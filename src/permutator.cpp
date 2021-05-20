#include "pch.h"
#include "permutator.h"
#include "fasta.h"
#include "monitor.h"
#include "menu.h"

namespace permutator
{
	vector<unsigned char> cartesianResults;
	vector<vector<unsigned char>> sets;

	vector<size_t> moduli;
	vector<int> divisions;

	size_t maxSetSize = 1;
}

static void prepare_chunks(vector<string>&& vec, size_t size, size_t inputSize)
{
	vec.reserve(size);
	for (auto& element : vec)
		element.reserve(inputSize);
}

void permutator::execute()
{
	program_data::permutationTime += Bench(lazy_permutation);
}

void permutator::insert_chunk(vector<string>&& chunkResults, size_t& chunksWritten, ofstream&& fastaOut)
{
	program_data::writeFastaTime += Bench(fasta::write_vector,
		std::move(chunkResults), std::move(fastaOut));
	if (program_data::writeDebug)
		menu::write_chunk(chunksWritten);

	chunksWritten++;
	chunkResults.clear();
}

unsigned char permutator::lazy_cartesian(size_t j, size_t i)
{
	if ((size_t)j >= program_data::get_lazy_cartesian_size())
		throw "Invalid index. Please contact the software developer.";

	vector<unsigned char> combinations;
	combinations.reserve(maxSetSize);

	for (size_t r = 0; r < sets.size(); r++)
	{
		auto a = int(floor(j / divisions[r])) % moduli[r];
		combinations.push_back(sets[r][a]);
	}

	return combinations[i];
}

void permutator::lazy_preparation()
{
	size_t inputSize = program_data::get_input_size();

	sets.clear();
	sets.reserve(inputSize);

	for (size_t i = 0; i < inputSize; i++)
	{
		for (auto& unit : program_data::unitList)
			if (program_data::input[i] == unit.second.GetDegenerateBase())
			{
				if (unit.first == 1)
					sets.push_back({ 0 });
				else if (unit.first == 2)
					sets.push_back({ 0, 1 });
				else if (unit.first == 3)
					sets.push_back({ 0, 1, 2 });
				else if (unit.first == 4)
					sets.push_back({ 0, 1, 2, 3 });
			}
	}

	size_t setsSize = sets.size();

	divisions.resize(setsSize);
	moduli.resize(setsSize);

	int factor = 1;
	for (int i = setsSize - 1; i >= 0; --i)
	{
		size_t item = sets[i].size();

		divisions.insert(divisions.begin(), factor);
		moduli.insert(moduli.begin(), item);

		factor *= item;
	}
}

void permutator::simple_base_insertion()
{
	ofstream fastaOut;
	fasta::open_file(std::move(fastaOut));

	fasta::write_result(std::move(program_data::input), std::move(fastaOut));

	program_data::outcomes++;

	fasta::close_file(std::move(fastaOut));
}

void permutator::lazy_permutation()
{
	if (!program_data::any_degenerate_bases())
	{
		simple_base_insertion();
		return;
	}

	lazy_preparation();

	vector<string> chunkResults = {};
	prepare_chunks(std::move(chunkResults), program_data::chunkSize, program_data::get_input_size());

	if (program_data::writeDebug)
		menu::write_chunk_size();

	ofstream fastaOut;
	fasta::open_file(std::move(fastaOut));

	string result;
	size_t chunksWritten = 1;
	for (size_t j = 0; j < program_data::get_lazy_cartesian_size(); ++j)
	{
		for (size_t i = 0; i < program_data::get_input_size(); ++i)
		{
			auto cartesian = lazy_cartesian(j, i);

			for (auto& unit : program_data::unitList)
			{
				if (program_data::input[i] == unit.second.GetDegenerateBase())
				{
					result += *(&unit.second.GetPossibleBases()[cartesian]);
					break;
				}
			}

			program_data::iterations++;
		}

		if (chunkResults.size() == program_data::chunkSize)
			insert_chunk(std::move(chunkResults), chunksWritten, std::move(fastaOut));

		chunkResults.push_back(result);
		result.clear();

		program_data::outcomes++;
	}

	if (!chunkResults.empty())
		insert_chunk(std::move(chunkResults), chunksWritten, std::move(fastaOut));

	if (program_data::get_lazy_cartesian_size() != program_data::outcomes)
		menu::unmatched_bases_errors();

	cout << std::dec << '\n';

	fasta::close_file(std::move(fastaOut));
}
