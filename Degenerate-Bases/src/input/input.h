#pragma once

namespace dgn
{
	class Input
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