#pragma once
#include "../data.h"

namespace dgn
{
	class Permutator
	{
	private:
		typedef uint_least32_t least;
		typedef const std::vector<std::function<void(const std::string&)>> writters;

	public:
		static void LazyPermutation(least min = 0, least max = Data::cartesianSize);

		static void SimpleBaseInsertion();

		static void Preparation();

	private:
		static unsigned char LazyCartesian(least j, least i);

	private:
		static inline std::vector<std::vector<unsigned char>> s_Sets = {};

		static inline std::vector<size_t> s_Moduli = {};

		static inline std::vector<int> s_Divisions = {};
	};
}