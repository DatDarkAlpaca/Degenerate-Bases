#include "pch.h"
#include "data.h"
#include "srwa/srwa.h"
#include "permutator.h"
#include "settings/settings.h"

static void WriteTimed(const std::string& data)
{
	using namespace dgn;

	high_resolution_clock::time_point begin = high_resolution_clock::now();
	SRWA::Write(data);
	high_resolution_clock::time_point end = high_resolution_clock::now();

	Data::writeFastaTime += duration_cast<nanoseconds>(end - begin).count() / 1'000'000;
}

void dgn::Permutator::LazyPermutation()
{
	Preparation();

	std::string result;
	result.reserve(Data::sequence.size());

	for (size_t i = 0; i < Data::cartesianSize; ++i)
	{
		for (size_t j = 0; j < Data::sequence.size(); ++j)
		{
			auto cartesian = LazyCartesian(i, j);

			for (auto& [baseName, base] : Data::validBases)
			{
				if (Data::sequence[j] == baseName)
				{
					result += base.basePossibilities[cartesian];
					break;
				}
			}

			Data::iterations++;
		}

		WriteTimed(result);

		result.clear();

		Data::outcomes++;
	}
}

void dgn::Permutator::SimpleBaseInsertion(const std::string& filepath)
{
	SRWA::Open(filepath);

	SRWA::Write(Data::sequence);

	SRWA::Close();

	Data::outcomes = 1;
}

void dgn::Permutator::Preparation()
{
	size_t inputSize = Data::sequence.size();

	s_Sets.clear();
	s_Sets.reserve(inputSize);

	for (size_t i = 0; i < inputSize; i++)
	{
		for (const auto& [baseName, base] : Data::validBases)
		{
			if (Data::sequence[i] == baseName)
			{
				switch (base.baseSize)
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

unsigned char dgn::Permutator::LazyCartesian(least i, least j)
{
	if ((size_t)i >= Data::cartesianSize)
		return 0;

	std::vector<unsigned char> combinations;
	combinations.reserve(Data::sequence.size());

	for (size_t r = 0; r < s_Sets.size(); r++)
	{
		unsigned int a = int(floor(i / s_Divisions[r])) % s_Moduli[r];
		combinations.push_back(s_Sets[r][a]);
	}

	return combinations[j];
}
