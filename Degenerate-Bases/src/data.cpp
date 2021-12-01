#include "pch.h"
#include "data.h"

const std::unordered_map<char, unsigned short> dgn::Data::validBases = {
	{ 'N', 4 },
	{ 'D', 3 },
	{ 'V', 3 },
	{ 'B', 3 },
	{ 'H', 3 },
	{ 'W', 2 },
	{ 'S', 2 },
	{ 'K', 2 },
	{ 'M', 2 },
	{ 'Y', 2 },
	{ 'R', 2 },
	{ 'A', 1 },
	{ 'C', 1 },
	{ 'G', 1 },
	{ 'T', 1 },
	{ '.', 1 },
	{ '-', 1 },
	{ '*', 1 },
};

std::unordered_map<unsigned short, unsigned int> dgn::Data::baseSizes = {
	{ 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 },
};

std::unordered_map<char, std::vector<char>> dgn::Data::units = {
	{ '.', {'.'} },
	{ '-', {'-'} },
	{ '*', {'*'} },

	{ 'A', { 'A' } },
	{ 'C', { 'C' } },
	{ 'G', { 'G' } },
	{ 'T', { 'T' } },

	{ 'W', { 'A', 'T' } },
	{ 'S', { 'C', 'G' } },
	{ 'K', { 'G', 'T' } },
	{ 'M', { 'A', 'C' } },
	{ 'Y', { 'C', 'T' } },
	{ 'R', { 'A', 'G' } },

	{ 'D', { 'A', 'G', 'T' } },
	{ 'V', { 'A', 'C', 'G' } },
	{ 'B', { 'C', 'G', 'T' } },
	{ 'H', { 'A', 'C', 'T' } },

	{ 'N', { 'A', 'C', 'T', 'G' } }
};