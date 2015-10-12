#include "../include/Map.h"
#include <iostream>
#include <cstring>

namespace solver
{
	Status Map::get(int x, int y) const
	{
		// êŒÇÃ1zkÇÕÇ©Ç»ÇÁÇ∏É}ÉbÉvè„Ç…Ç†ÇÈ
//		std::cout << x << "," << y << std::endl;
//		assert(-8 < x && x < 39 && -8 < y && y < 39);
		assert(-9 < x && x < 40 && -9 < y && y < 40);

		if (0 <= x && x < 32 && 0 <= y && y < 32)
			return _map[y][x];

		return Status::OBSTACLE;
	}

	Status & Map::set(int x, int y)
	{
		assert(0 <= x && x < 32 && 0 <= y && y < 32);

		return _map[y][x];
	}

	std::string Map::dump() const
	{
		std::string str = "START\r\n";

		for (int y = 0; y < 32; y++)
		{
			for (int x = 0; x < 32; x++)
				str.append(StatusToString(get(x, y)));

			str.append(endl);
		}

		return str;
	}

	bool Map::operator==(const Map &b) const
	{
		return std::memcmp(_map, b._map, sizeof(_map)) == 0;
	}

	int Map::zk() const
	{
		return _zk;
	}

	int Map::perimeter() const
	{
		return _perimeter;
	}

	void Map::evalStone(int x, int y)
	{
		assert(0 <= x && x < 32 && 0 <= y && y < 32);

		auto &stone = this->set(x, y);

//		assert(stone != Status::OBSTACLE && stone != Status::STONE);

		int neighborStoneCount = 0;

		for (const auto & neighborChord : neighborChords)
		{
			auto mapX = x + neighborChord.first;
			auto mapY = y + neighborChord.second;
			auto neighborStatus = this->get(mapX, mapY);

			if (neighborStatus == Status::OBSTACLE || neighborStatus == Status::STONE)
				neighborStoneCount++;
		}

		_perimeter += 4 - neighborStoneCount * 2;
		_zk++;
	}
}
