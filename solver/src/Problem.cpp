#include "../include/Problem.h"
#include "../include/utils/ProblemLoader.h"
#include "../include/utils/Util.h"
#include <iostream>
#include <sstream>
#include <cassert>

namespace solver
{
	Problem::Problem(std::istream &ifs)
	{
		assert(ProblemLoader::run(_map, _stones, _stoneCount, ifs));
	}

	std::string Problem::dump()
	{
		std::string str = "";

		// dump _map
		str.append(_map.dump());

		// dump stoneCount
		str.append("\n");
		str.append(std::to_string(_stoneCount));
		str.append("\n");

		// dump _stones
		for (int i = 0; i < _stoneCount; i++)
		{
			str.append(_stones[i].dump());

			if (i != _stoneCount - 1)
				str.append("\n");
		}

		return str;
	}

}