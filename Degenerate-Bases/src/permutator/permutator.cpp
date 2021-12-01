#include "pch.h"
#include "permutator.h"

#include "../data.h"
#include "../fasta/chunk.h"
#include "../fasta/fasta.h"

void dgn::Permutator::Execute()
{
	// SBI:
	if (!Data::anyDegenerate)
		return SimpleBaseInsertion();

	Preparation();

	LazyPermutation();
}

void dgn::Permutator::Preparation()
{
	size_t inputSize = Data::sequence.size();

	s_Sets.clear();
	s_Sets.reserve(inputSize);

	for (size_t i = 0; i < inputSize; i++)
	{
		for (auto& unit : Data::units)
		{
			if (Data::sequence[i] == unit.first)
			{
				switch (unit.second.size())
				{
				case 1:
					s_Sets.push_back({ 0 });
					break;

				case 2:
					s_Sets.push_back({ 0, 1 });
					break;

				case 3:
					s_Sets.push_back({ 0, 1, 2 });
					break;

				case 4:
					s_Sets.push_back({ 0, 1, 2, 3 });
					break;
				}
			}
		}
	}

	size_t setsSize = s_Sets.size();

	s_Divisions.resize(setsSize);
	s_Moduli.resize(setsSize);

	int factor = 1;
	for (int i = setsSize - 1; i >= 0; --i)
	{
		size_t item = s_Sets[i].size();

		s_Divisions.insert(s_Divisions.begin(), factor);
		s_Moduli.insert(s_Moduli.begin(), item);

		factor *= item;
	}
}

unsigned char dgn::Permutator::LazyCartesian(size_t j, size_t i)
{
	if ((size_t)j >= Data::cartesianSize)
	{
		return 0;
		// Todo: show an error.
	}

	std::vector<unsigned char> combinations;
	combinations.reserve(Data::sequence.size());

	for (size_t r = 0; r < s_Sets.size(); r++)
	{
		unsigned int a = int(floor(j / s_Divisions[r])) % s_Moduli[r];
		combinations.push_back(s_Sets[r][a]);
	}

	return combinations[i];
}

void dgn::Permutator::SimpleBaseInsertion()
{
	// Write to fasta if enabled.
	// Add to the results list.
	// Write to the history list.
}

void dgn::Permutator::LazyPermutation()
{
	// Todo: Set capacity.
	std::string result;
	result.reserve(Data::sequence.size());

	Fasta::Open("");

	for (size_t j = 0; j < Data::cartesianSize; ++j)
	{
		for (size_t i = 0; i < Data::sequence.size(); ++i)
		{
			auto cartesian = LazyCartesian(j, i);

			for (auto& unit : Data::units)
			{
				if (Data::sequence[i] == unit.first)
				{
					result += unit.second[cartesian];
					break;
				}
			}

			Data::iterations++;
		}

		Chunk::Insert(result);
		
		{
			// Todo: if full
			// Fasta::Write(Chunk::data);
			// Save to fasta.
			// Add results to list like a generator.
			// Chunk::Empty();
		}

		result.clear();

		Data::outcomes++;
	}

	Fasta::Close();
}
