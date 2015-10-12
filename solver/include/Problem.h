#pragma once

#include <istream>
#include <memory>
#include "Map.h"
#include "Stone.h"

namespace solver
{
	class Problem
	{
	public:
		Problem(std::istream &ifs);
		std::string dump();

		Map _map;
		std::unique_ptr<Stone[]> _stones;

		int _stoneCount;
	};
}