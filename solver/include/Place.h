#pragma once

#include <string>
#include <cstdint>
#include "Stone.h"
#include "utils/Util.h"

namespace solver
{
	class Place
	{
	public:
		bool _skip;
		bool _up;
		Direction _dir;
		int8_t _x;
		int8_t _y;

		std::string toString() const;
	};
}