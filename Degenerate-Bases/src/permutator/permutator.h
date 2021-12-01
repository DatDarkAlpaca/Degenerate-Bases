#pragma once

namespace dgn
{
	class Permutator
	{
	public:
		static void Execute();

	private:
		static unsigned char LazyCartesian(size_t j, size_t i);

		static void SimpleBaseInsertion();

		static void Preparation();

		static void LazyPermutation();

	private:
		static inline std::vector<std::vector<unsigned char>> s_Sets = {};

		static inline std::vector<size_t> s_Moduli = {};

		static inline std::vector<int> s_Divisions = {};
	};
}