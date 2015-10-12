#pragma once
#include <cassert>
#include <cstdint>
#include <cstddef>

namespace solver
{
	struct Point;

	size_t hash_value(const Point &obj);

	struct Point
	{
		int8_t _x;
		int8_t _y;

		Point() : _x(0), _y(0) {}
		Point(int8_t x, int8_t y) : _x(x), _y(y) {}

		bool operator==(const Point& target) const
		{
			return (_x == target._x) && (_y == target._y);
		}

		bool operator!=(const Point& target) const
		{
			return !(*this == target);
		}

		bool operator<(const Point & target) const
		{
			return hash_value(*this) < hash_value(target);
		}

		Point operator-(const Point &b) const
		{
			return Point(_x - b._x, _y - b._y);
		}
	};
}
