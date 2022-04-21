#pragma once

namespace dgn
{
	class Permutator
	{
	private:
		using least = uint_least32_t;

	public:
		static void LazyPermutation();

		static void SimpleBaseInsertion(const std::string& filepath);

	private:
		static void Preparation();

		static unsigned char LazyCartesian(least i, least j);

	private:
		static inline std::vector<std::vector<unsigned char>> s_Sets = {};

		static inline std::vector<size_t> s_Moduli = {};

		static inline std::vector<int> s_Divisions = {};
	};
}