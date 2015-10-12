#pragma once

#include "utils/Point.h"
#include "utils/Util.h"
#include <array>

namespace solver
{
	struct Path
	{
	public:
		Point _start;
		Point _end;

		Path() : _start(Point(0, 0)), _end(Point(0, 0)) {}
		Path(Point start, Point end) : _start(start), _end(end) {}
		
		Path reverse() const;
		bool operator==(const Path& target) const;
		bool operator==(const Point& point) const;
		bool isConnected(const Path& next) const;
		Path connectable(const Path& next) const;
		operator bool() const;
		
		static std::array<Path, 2> squareNeighborPath(uint8_t x, uint8_t y, Position pos);
		static std::array<Path, 8> squareNeighborPath(uint8_t x, uint8_t y);
		static std::array<Path, 4> squarePath(uint8_t x, uint8_t y);
	};
}