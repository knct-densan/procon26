#pragma once

#include <cstdint>
#include <vector>
#include <list>
#include "Polygon.h"
#include "Map.h"

namespace solver
{
	class Polygons
	{
	public:
		Polygons() {}
		Polygons(const Map& map);
		bool applyStone(uint8_t x, uint8_t y);

		unsigned int area() const;
		unsigned int polygonCount() const;
		unsigned int perimeter() const;

		double averageEmpty() const;
		double complextity() const;

	private:
		unsigned int _area;
		std::vector<Polygon> _children;

		std::list<Polygon> merge(
			int8_t x,
			int8_t y,
			const std::list<Polygon> &poly) const;

		std::list<Polygon> merge(
			int8_t x,
			int8_t y,
			const Polygon &poly) const;

		std::vector<Path> makeLoop(int8_t x, int8_t y, std::vector<Path> &path, const bool usableSquareFlag[8]) const;

		std::list<Path> makePath(
			int8_t x,
			int8_t y,
			Position start,
			Position end,
			bool clockwise
			) const;

		bool decideSquarePath(
			std::list<std::vector<Path>> &loops,
			int8_t x,
			int8_t y,
			bool usableSquarePath[4]) const;

		bool _decideSquarePath(
			std::list<std::vector<Path>> &loops,
			int8_t x,
			int8_t y,
			bool clockwise,
			bool usableSquarePath[4]) const;

		bool isPointSquare(int8_t x, int8_t y, Point point) const;

		Position pointToPosition(int8_t x, int8_t y, Point point) const;
		Position pathToPosition(int8_t x, int8_t y, Path path) const;

		int8_t pathToSquarePathId(int8_t x, int8_t y, Path path) const;

		bool connectable(const std::vector<Path> &first, const std::vector<Path> &second) const;
		void connect(std::vector<Path> &first, std::vector<Path> &second) const;
	};
}