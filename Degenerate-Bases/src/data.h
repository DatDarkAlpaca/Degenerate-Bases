#pragma once

namespace dgn
{
	struct Base
	{
	public:
		Base(char baseName, unsigned short baseSize, std::vector<char>&& possibleBases)
			: baseName(baseName), baseSize(baseSize), basePossibilities(possibleBases) { }

	public:
		char baseName;
		unsigned short baseSize;
		std::vector<char> basePossibilities;
	};

	struct Data
	{
	public:
		static void Clear()
		{
			for (auto& base : baseSizes)
				base.second = 0;

			permutationTime = 0;
			writeFastaTime = 0;

			iterations = 0;
			outcomes = 0;

			invalidSequence = false;
			anyDegenerate = false;
			sequence = "";
		}

	public: /* Sequence Data */
		static inline std::string sequence = "";
		static inline uint_least32_t cartesianSize = 0;

	public: /* Status Data */
		static inline bool invalidSequence = false;
		static inline bool anyDegenerate = false;

	public: /* Unit Data */
		static inline const std::unordered_map<char, Base> validBases = {
			{ 'N', Base('N', 4, { 'A', 'C', 'T', 'G'})},
			{ 'D', Base('D', 3, { 'A', 'G', 'T' })},
			{ 'V', Base('V', 3, { 'A', 'C', 'G' })},
			{ 'B', Base('B', 3, { 'C', 'G', 'T' })},
			{ 'H', Base('H', 3, { 'A', 'C', 'T' })},

			{ 'W', Base('W', 2, { 'A', 'T' })},
			{ 'S', Base('S', 2, { 'C', 'G' })},
			{ 'K', Base('K', 2, { 'G', 'T' })},
			{ 'M', Base('M', 2, { 'A', 'C' })},
			{ 'Y', Base('Y', 2, { 'C', 'T' })},
			{ 'R', Base('R', 2, { 'A', 'G' })},

			{ 'A', Base('A', 1, { 'A' }) },
			{ 'C', Base('C', 1, { 'C' }) },
			{ 'G', Base('G', 1, { 'G' }) },
			{ 'T', Base('T', 1, { 'T' }) },

			{ '.', Base('.', 1, { '.' }) },
			{ '-', Base('-', 1, { '-' }) },
			{ '*', Base('*', 1, { '*' }) },
		};

		static inline std::unordered_map<unsigned short, unsigned int> baseSizes = {
			{ 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 },
		};
	
	public: /* Results Data */
		static inline std::atomic<uint32_t> iterations{ 0 }, outcomes{ 0 };

	public: /* Warning Data */
		static inline uint32_t warningCartesianSize = 2 << 22;
		static inline size_t warningResultsSize = 100;

	public: /* Timing Data */
		static inline std::atomic<long long> writeFastaTime{ 0 }, permutationTime{ 0 };
	};
}