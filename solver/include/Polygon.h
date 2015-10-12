#pragma once

#include "Path.h"
#include "utils/Point.h"
#include <list>
#include <vector>

namespace solver
{
	struct Polygon
	{
		Polygon();
		Polygon(uint8_t x, uint8_t y);
		Polygon(std::vector<Path> &paths);

		std::list<Path> _paths;
		std::vector<Polygon> _children;

		unsigned int perimeter() const;
		unsigned int polygonCount() const;

		bool contain(const Point &point) const;
		bool contain(const Polygon &poly) const;
		bool conflict(const Path &path) const;
		unsigned int conflict(const Polygon &poly) const;
		bool plusConflict(uint8_t x, uint8_t y) const;

		bool operator==(const Polygon &poly) const;

		bool _isEmpty;
	};
}