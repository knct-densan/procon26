#pragma once

#include <istream>
#include <memory>
#include "../Map.h"
#include "../Stone.h"

namespace solver
{
	class ProblemLoader
	{
	public:
		static bool run(
			Map &map,
			std::unique_ptr<Stone[]> &stones,
			int &stoneCount,
			std::istream &ifs
			);
	};
}