#pragma once

#include <cassert>
#include <string>
#include "utils/Util.h"

namespace solver
{
	class Map
	{
	public:
		Map() : _zk(0), _perimeter(32 * 32) {}

		Status get(int x, int y) const;
		Status &set(int x, int y);
		std::string dump() const;

		bool operator==(const Map &b) const;
		int zk() const;
		int perimeter() const;
		void evalStone(int x, int y);

	private:
		Status _map[32][32];
		int _zk;
		int _perimeter;
	};
}