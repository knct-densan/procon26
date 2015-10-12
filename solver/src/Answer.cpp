#include <cassert>
#include "../include/Answer.h"
#include "../include/Evaler.h"
#include "../include/Hasher.h"
#include "../include/utils/Util.h"
#include <iostream>
#include <algorithm>

namespace solver
{
	std::vector<int> Answer::_evals;

	Answer::Answer() {}

	Answer::Answer(const Problem &prob)
	{
		_map = Map(prob._map);
//		_polys = Polygons(prob._map);
		_stones = prob._stones.get();
		_stoneCount = prob._stoneCount;
		_first = true;
		_neighbors = std::vector<Point>();
		_hash = Hasher::hash(*this);
		_used = 0;
	}

	void Answer::setup(const std::vector<int> &evals)
	{
		_evals = evals;
	}

	int Answer::zk() const
	{
		return _map.zk();
	}

	HASH_TYPE Answer::hash() const
	{
		return _hash;
	}
	
	bool Answer::checkPlacement
		(
		int xOrigin,
		int yOrigin,
		bool up,
		Direction dir
		)
	{
		assert(_places.size() < _stoneCount);

		Stone &stone = _stones[_places.size()];

		if (_first) // 1個も石が置かれていない
		{
			for (int x = 0; x < 10; x++)
			{
				for (int y = 0; y < 10; y++)
				{
						auto mapX = x + xOrigin - 1;
						auto mapY = y + yOrigin - 1;
						auto mapStatus = _map.get(mapX, mapY);
						auto stoneStatus = stone.get(up, dir, x, y);

					if (stoneStatus == Status::STONE && mapStatus == Status::OBSTACLE)
						return false;
				}
			}

			return true;
		}
		else // 1個以上石が置かれている
		{
			bool neighbor = false;

			for (int x = 0; x < 10; x++)
			{
				for (int y = 0; y < 10; y++)
				{
					auto mapX = x + xOrigin - 1;
					auto mapY = y + yOrigin - 1;
					auto mapStatus = _map.get(mapX, mapY);
					auto stoneStatus = stone.get(up, dir, x, y);

					if (stoneStatus == Status::STONE &&
						(mapStatus == Status::OBSTACLE || mapStatus == Status::STONE))
						return false;
					/*
					neighbor |= (stoneStatus + mapStatus) == 5;
					*/
					/*
						(stoneStatus == Status::NEIGHBOR && mapStatus == Status::STONE) ||
						(stoneStatus == Status::STONE && mapStatus == Status::NEIGHBOR);
						*/
					
					if ( !neighbor && (stoneStatus == Status::NEIGHBOR && mapStatus == Status::STONE) ||
						(stoneStatus == Status::STONE && mapStatus == Status::NEIGHBOR))
						neighbor = true;
				}
			}

			return neighbor;
		}
	}

	bool Answer::applyPlacement(
		int xOrigin,
		int yOrigin,
		bool up,
		Direction dir
		)
	{
		assert(_places.size() < _stoneCount);

		if (checkPlacement(xOrigin, yOrigin, up, dir))
		{
			Stone &stone = _stones[_places.size()];

			if (_first) // 1個も石が置かれていない
			{
				for (int x = 0; x < 10; x++)
				{
					for (int y = 0; y < 10; y++)
					{
						auto mapX = x + xOrigin - 1;
						auto mapY = y + yOrigin - 1;
						auto mapStatus = _map.get( mapX, mapY );
						auto stoneStatus = stone.get(up, dir, x, y);

						if (stoneStatus == Status::STONE)
							_map.evalStone(mapX, mapY);

						if (mapStatus == Status::EMPTY)
						{
							_map.set(mapX, mapY) = stoneStatus;

							if (stoneStatus == Status::NEIGHBOR)
								_neighbors.push_back(Point(mapX, mapY));
						}
					}
				}
				_first = false;
			}
			else // 1個以上石が置かれている
			{
				for (int x = 0; x < 10; x++)
				{
					for (int y = 0; y < 10; y++)
					{
						auto mapX = x + xOrigin - 1;
						auto mapY = y + yOrigin - 1;
						auto mapStatus = _map.get(mapX, mapY);
						auto stoneStatus = stone.get(up, dir, x, y);

						if (stoneStatus == Status::STONE)
							_map.evalStone(mapX, mapY);

						if (mapStatus == Status::EMPTY)
						{
							_map.set(mapX, mapY) = stoneStatus;

							if (stoneStatus == Status::NEIGHBOR)
								_neighbors.push_back(Point(mapX, mapY));
						}
						else if (mapStatus == Status::NEIGHBOR)
						{
							if (stoneStatus == Status::STONE)
							{
								_map.set(mapX, mapY) = Status::STONE;
								remove(_neighbors, Point(mapX, mapY));
							}
						}
					}
				}
			}

			Place newPlace;
			newPlace._skip = false;
			newPlace._up = up;
			newPlace._dir = dir;
			newPlace._x = xOrigin;
			newPlace._y = yOrigin;

			_places.push_back(newPlace);

			_used++;
			_hash ^= Hasher::hash(*this, newPlace, stone);

			// TODO: Evalerの呼び出し
			for (int i = 0; i < EVALER_NUM; i++)
				_evalResult[i] = Evaler::eval(*this, i);

			return true;
		}
		else
			return false;
	}

	void Answer::skipStone()
	{
		assert(_places.size() < _stoneCount);

		Place newPlace;
		newPlace._skip = true;

		_places.push_back(newPlace);
	}

	std::string Answer::getAnswer() const
	{
		assert( _places.size() == _stoneCount );

		std::string answer = "";

//		answer += "answerSTART" + solver::endl;

		for (unsigned int i = 0; i < _places.size(); i++)
			answer += _places[i].toString();

//		answer += "answerEND" + solver::endl;

		return answer;
	}

	bool Answer::operator>(const Answer &b) const
	{
		return b < *this;
	}

	bool Answer::operator<(const Answer &b) const
	{
		bool last;

		for (auto eval : _evals)
		{
			auto mode = std::abs(eval) - 1;
			auto thisStatus = _evalResult[mode];
			auto anotherStatus = b._evalResult[mode];

			if (thisStatus != anotherStatus)
			{
				if (eval > 0)
					return thisStatus < anotherStatus;
				else
					return anotherStatus < thisStatus;
			}
			else
			{
				if (eval > 0)
					last = thisStatus < anotherStatus;
				else
					last = anotherStatus < thisStatus;
			}
		}

		return last;
	}

	bool Answer::operator == (const Answer &b) const
	{
		return _map == b._map;
	}

	bool Answer::first() const
	{
		return _first;
	}

	int Answer::used() const
	{
		return _used;
	}
}
