#pragma once

#include "Answer.h"

namespace solver
{
	class Answer;
	class Evaler
	{
	public:
		static double eval(const Answer &answer);
		static void setup(const Problem &prob);
		static double eval(const Answer &answer, int type);

	private:
		static bool _setup;
		static std::vector<int> _stoneAreaSum;

		static int placed(const Answer &answer);
		static double averageEmptyPerHoles(const Answer &answer);
		static double averageEmptyPerPerimeter(const Answer &answer);
		static int errorRemainingArea(const Answer &answer);
		static int neighbors(const Answer &answer);
		static int used(const Answer &answer);
	};
}