#include "pch.h"
#include "permutator.h"
#include "../data.h"

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

unsigned char dgn::Permutator::LazyCartesian(least j, least i)
{
	if ((size_t)j >= Data::cartesianSize)
	{
		// Todo: error.
		return 0;
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

void dgn::Permutator::SimpleBaseInsertion(writters&& writterFunctions)
{
	for (const auto& writter : writterFunctions)
		writter(Data::sequence);
}

void dgn::Permutator::LazyPermutation(least min, least max, writters writterFunctions)
{
	// SBI:
	if (!Data::anyDegenerate)
		return SimpleBaseInsertion(std::move(writterFunctions));

	// Lazy algorithm preparation:
	Preparation();

	// Reserving the result string:
	std::string result;
	result.reserve(Data::sequence.size());

	for (size_t j = min; j < max; ++j)
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

		// Writting:
		for (const auto& writter : writterFunctions)
			writter(result);

		result.clear();

		Data::outcomes++;
	}
}
