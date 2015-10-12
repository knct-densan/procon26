#pragma once

#include <vector>
#include <string>
#include "utils/Util.h"
#include "Polygons.h"
#include "Problem.h"
#include "Place.h"
#include "Stone.h"
#include "utils/Point.h"
#include "Evaler.h"

namespace solver
{
	class Evaler;

	class Answer
	{
	public:
		Answer();
		Answer(const Problem &prob);
		
		static void setup(const std::vector<int> &evals);

		bool applyPlacement(
			int xOrigin,
			int yOrigin,
			bool up,
			Direction dir
			);

		void skipStone();

		std::string getAnswer() const;;

		Map _map;
		Stone *_stones = nullptr;
		
		std::vector<Place> _places;
		std::vector<Point> _neighbors;

		unsigned int _stoneCount;

		bool operator < (const Answer &b) const;
		bool operator > (const Answer &b) const;

		bool operator == (const Answer &b) const;

		bool first() const;
		int zk() const;
		int used() const;
		HASH_TYPE hash() const;

	private:
		static std::vector<int> _evals;
		bool _first;
		bool checkPlacement(
			int xOrigin,
			int yOrigin,
			bool up,
			Direction dir
			);
		double _evalResult[EVALER_NUM];

		HASH_TYPE _hash;
		int _used;
	};
}

namespace std
{
	template <> class hash<solver::Answer>
	{
	public:
		size_t operator()(const solver::Answer & x) const
		{
			return x.hash();
		}
	};
}