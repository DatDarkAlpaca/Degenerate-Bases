#pragma once
#include "pch.h"

namespace dgn
{
	struct Chunk
	{
	public:
		static void Prepare(size_t chunkSize, size_t sequenceSize)
		{
			data.resize(chunkSize);
			maximumSize = chunkSize;
		}

		static void Insert(const std::string& result)
		{
			data.push_back(result);

			if (data.size() >= maximumSize)
				full = true;
		}

		static void Clear()
		{
			data.clear();
			full = false;
		}

	public:
		static inline std::vector<std::string> data;
		static inline size_t maximumSize = 0;
		static inline bool full = false;
	};
}