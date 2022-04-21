#include "pch.h"
#include "data.h"
#include "input.h"

void dgn::Input::SanitizeInput()
{
	EmptySequence();

	if (Data::invalidSequence)
		return;

	Capitalize();

	PurgeExcess();

	CountBases();

	AnyDegenerate();

	ComputeCartesianSize();
}

void dgn::Input::EmptySequence()
{
	Data::invalidSequence = Data::sequence.empty();
}

void dgn::Input::Capitalize()
{
	std::transform(Data::sequence.begin(), Data::sequence.end(), Data::sequence.begin(), ::toupper);
}

void dgn::Input::PurgeExcess()
{
	// Getting only the bases:
	std::vector<char> bases;
	for (const auto& base : Data::validBases)
		bases.push_back(base.first);

	// Removing invalid bases:
	Data::sequence.erase(std::remove_if(Data::sequence.begin(), Data::sequence.end(), [&bases](char& c) {
			return !(std::find(bases.begin(), bases.end(), c) != bases.end());
		}), Data::sequence.end());

	// Check whether there are any valid sequences:
	if (Data::sequence.empty())
		Data::invalidSequence = true;
}

void dgn::Input::CountBases()
{
	for (const auto& character : Data::sequence)
	{
		for (const auto& [baseName, base] : Data::validBases)
		{
			if (character == baseName)
				Data::baseSizes[base.baseSize] += 1;
		}
	}
}

void dgn::Input::AnyDegenerate()
{
	Data::anyDegenerate = (Data::baseSizes[4] > 0 ||
						   Data::baseSizes[3] > 0 ||
						   Data::baseSizes[2] > 0);
}

void dgn::Input::ComputeCartesianSize()
{
	uint_least32_t size = 1;

	if (Data::baseSizes[4] > 0) size *= (uint_least32_t)pow(4, Data::baseSizes[4]);
	if (Data::baseSizes[3] > 0)	size *= (uint_least32_t)pow(3, Data::baseSizes[3]);
	if (Data::baseSizes[2] > 0)	size *= (uint_least32_t)pow(2, Data::baseSizes[2]);

	Data::cartesianSize = size;
}
