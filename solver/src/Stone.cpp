#include <cassert>
#include <cstring>
#include "../include/Stone.h"
#include "../include/utils/Util.h"

namespace solver
{
	Stone::Stone()
	{
		_setup = false;
		std::memset(_stone, 0, sizeof(_stone));
	}

	Status Stone::get(int x, int y) const
	{
		assert(0 <= x && x < 10 && 0 <= y && y < 10);
		assert(_setup);

		return get(true, Direction::UL, x, y);
	}

	Status Stone::get(bool up, Direction dir, int x, int y) const
	{
		assert(0 <= x && x < 10 && 0 <= y && y < 10);
		assert(_setup);

		return _stone[up ? 0 : 1][(int)dir][y][x];
	}

	Status & Stone::set(int x, int y)
	{
		assert(0 <= x && x < 8 && 0 <= y && y < 8);
		assert(!_setup);

		return _stone[0][0][y + 1][x + 1];
	}

	void Stone::setup()
	{
		_setup = true;

		markNeighbor();
		makeUpDownAndDirections();

		_size = 0;

		for (int y = 1; y < 9; y++)
			for (int x = 1; x < 9; x++)
				_size += (_stone[0][0][y][x] == Status::STONE ? 1 : 0);

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int y = 1; y < 9; y++)
				{
					for (int x = 1; x < 9; x++)
					{
						if (_stone[i][j][y][x] == Status::STONE)
							_stonePos[i][j].push_back(Point(x, y));
					}
				}
			}
		}
	}

	const std::vector<Point> & Stone::stonePos(bool up, Direction dir) const
	{
		return _stonePos[up ? 0 : 1][(int)dir];
	}

	std::string Stone::dump(bool up, Direction dir)
	{
		std::string str = "";

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
				str.append(StatusToString(get(up, dir, x, y)));

			str.append("\n");
		}

		return str;
	}

	std::string Stone::dump()
	{
		return dump(true, Direction::UL);
	}

	int Stone::size()
	{
		return _size;
	}

	void Stone::markNeighbor()
	{
		// ‰¡‚ÉŒ©‚é
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				// ‰E‘¤‚ÉÎ‚ª‚ ‚é
				if (0 < x)
				{
					if (_stone[0][0][y][x] == Status::STONE &&
						_stone[0][0][y][x - 1] == Status::EMPTY
						)
						_stone[0][0][y][x - 1] = Status::NEIGHBOR;
				}
				// ¶‘¤‚ÉÎ‚ª‚ ‚é
				if (x < 9)
				{
					if (_stone[0][0][y][x] == Status::STONE &&
						_stone[0][0][y][x + 1] == Status::EMPTY
						)
						_stone[0][0][y][x + 1] = Status::NEIGHBOR;
				}
			}
		}

		// c‚ÉŒ©‚é
		for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{
				// ‰º‘¤‚ÉÎ‚ª‚ ‚é
				if (0 < y)
				{
					if (_stone[0][0][y][x] == Status::STONE &&
						_stone[0][0][y - 1][x] == Status::EMPTY
						)
						_stone[0][0][y - 1][x] = Status::NEIGHBOR;
				}
				// ã‘¤‚ÉÎ‚ª‚ ‚é
				if (y < 9)
				{
					if (_stone[0][0][y][x] == Status::STONE &&
						_stone[0][0][y + 1][x] == Status::EMPTY
						)
						_stone[0][0][y + 1][x] = Status::NEIGHBOR;
				}
			}
		}
	}

	void Stone::makeUpDownAndDirections()
	{
		makeUpDown();
		for (int i = 0; i < 2; i++)
			makeDirections(i);
	}

	void Stone::makeUpDown()
	{
		// make down
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				_stone[1][0][i][j] = _stone[0][0][i][10 - j - 1];
	}

	void Stone::makeDirections(int key)
	{
		// make directions
		for (int i = 1; i < 4; i++)
			Stone::makeRotate(key, i - 1, i);
	}

	void Stone::makeRotate(int key, int from, int to)
	{
		for (int y = 0; y < 10; y++)
			for (int x = 0; x < 10; x++)
				_stone[key][to][y][x] = _stone[key][from][10 - x - 1][y];
	}
}