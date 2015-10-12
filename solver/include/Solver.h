#pragma once

#include "Problem.h"
#include "Answer.h"
#include "Evaler.h"

namespace solver
{
	class Solver
	{
	public:
		static Answer Solve(Problem &prob);
		static void setup(int beam, bool bestFirst);

	private:
		static int _beam;
		static int _maxQueueSize;
		static bool _bestFirst;
	};
}