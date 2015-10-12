#include <random>
#include <cassert>
#include <cstdint>
#include <limits>

#include "../include/Hasher.h"

namespace solver
{
	// https://en.wikipedia.org/wiki/Zobrist_hashing

	bool Hasher::_first = true;
	HASH_TYPE Hasher::hashTable[32][32][2];

	HASH_TYPE Hasher::hash(const Answer &answer)
	{
		if (_first)
			makeHashTable();

		HASH_TYPE hash = 0;

		for (int y = 0; y < 32; y++)
		{
			for (int x = 0; x < 32; x++)
			{
				auto status = answer._map.get(x, y);
				hash ^= statusToHash(x, y, status);
			}
		}

		return hash;
	}

	HASH_TYPE Hasher::hash(const Answer &answer, const Place &place, const Stone &stone)
	{
		assert(!_first);

		HASH_TYPE hash = 0;

		auto &map = answer._map;
		auto xOrigin = place._x;
		auto yOrigin = place._y;
		auto up = place._up;
		auto dir = place._dir;

		for (int y = 1; y < 9; y++)
		{
			for (int x = 1; x < 9; x++)
			{
				auto mapX = x + xOrigin - 1;
				auto mapY = y + yOrigin - 1;
				auto before = map.get(mapX, mapY);
				auto next = stone.get(up, dir, x, y);
				auto beforeHash = statusToHash(mapX, mapY, before);
				auto nextHash = statusToHash(mapX, mapY, next);
				if (beforeHash != nextHash)
					hash ^= beforeHash ^ nextHash;
			}
		}

		return hash;
	}

	void Hasher::makeHashTable()
	{
		assert(_first);

		_first = false;

		std::random_device rd;
//		std::mt19937_64 mt(rd());
		std::mt19937_64 mt;

		for (int i = 0; i < 32; i++)
			for (int j = 0; j < 32; j++)
				for (int k = 0; k < 2; k++)
					hashTable[i][j][k] = mt();
	}

	HASH_TYPE Hasher::statusToHash(int x, int y, const Status &status)
	{
		if (0 <= x && x < 32 && 0 <= y && y < 32)
		{
			if (status == Status::EMPTY || status == Status::NEIGHBOR)
				return hashTable[y][x][0];
			else
				return hashTable[y][x][1];
		}
		else
			return 0;
	}
}
