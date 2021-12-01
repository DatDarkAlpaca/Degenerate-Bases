#pragma once
#include "pch.h"

namespace dgn
{
	class InputHandler
	{
	public:
		static void SanitizeInput();

	private:
		static void EmptySequence();

		static void AnyDegenerate();

		static void Capitalize();

		static void PurgeExcess();

		static void CountBases();

		static void ComputeCartesianSize();
	};
}