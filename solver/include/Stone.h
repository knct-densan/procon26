#pragma once

#include <vector>
#include <string>
#include "utils/Util.h"
#include "utils/Point.h"

namespace solver
{
	class Stone
	{
	public:
		Stone();
		void makeUpDownAndDirections();
		Status get(int x, int y) const;
		Status get(bool up, Direction dir, int x, int y) const;
		Status &set(int x, int y);
		void setup();
		std::string dump(bool up, Direction dir);
		std::string dump();
		const std::vector<Point> &stonePos(bool up, Direction dir) const;
		int size();
	
	private:
		Status _stone[2][4][10][10];
		std::vector<Point> _stonePos[2][4];
		int _size;

		bool _setup;

		void markNeighbor();
		void makeUpDown();
		void makeDirections(int key);
		void makeRotate(int key, int from, int to);
	};
}