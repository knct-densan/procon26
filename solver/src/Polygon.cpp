#include <cmath>
#include <cassert>
#include "../include/Polygon.h"
#include "../include/utils/Util.h"

namespace solver
{
	Polygon::Polygon()
	{
//		_parent = nullptr;
	}

	// 正方形を(x, y)を左上にして作る．
	Polygon::Polygon(uint8_t x, uint8_t y)
	{
		_isEmpty = false;
//		_parent = nullptr;

		// 下へ
		_paths.push_back(Path(Point(x, y), Point(x, y + 1)));
		// 右へ
		_paths.push_back(Path(Point(x, y + 1), Point(x + 1, y + 1)));
		// 上へ
		_paths.push_back(Path(Point(x + 1, y + 1), Point(x + 1, y)));
		// 左へ
		_paths.push_back(Path(Point(x + 1, y), Point(x, y)));
	}

	Polygon::Polygon(std::vector<Path> &paths)
	{
		_paths.insert(_paths.end(), ALL(paths));
	}

	unsigned int Polygon::perimeter() const
	{
		unsigned int sum = 0;

		for (const auto & child : _children)
			sum += child.perimeter();

		return sum + _paths.size();
	}

#define cross(a, b) ((a._x * b._y) - (a._y * b._x))
#define dot(a, b) (a._x * b._x + a._y * b._y)
	// ある点が多角形の内部(辺上を含む)にいるかどうか
	// ref: www.prefield.com/algorithm/geometry/contains.html
	bool Polygon::contain(const Point &point) const
	{
		bool in = false;
		
		for (const auto &path : _paths)
		{
			Point a = path._start - point; // 位置ベクトル
			Point b = path._end - point; // 位置ベクトル
			if (a._y > b._y) std::swap(a, b);
			if (a._y <= 0 && 0 < b._y) // 交差しているか
				if (cross(a, b) < 0) // 角度の確認(半直線)
					in = !in;
			if (cross(a, b) == 0 && dot(a, b) <= 0) return true;
		}

		return in;
	}
#undef cross
#undef dot

	// ある多角形が多角形の内部(辺上を含む)にいるかどうか
	bool Polygon::contain(const Polygon &poly) const
	{
		for (const auto &path : poly._paths)
		{
			if (!contain(path._start) && !contain(path._end) && !conflict(path))
				return false;
		}

		return true;
	}

	// ある辺が多角形の辺上にいるかどうか
	bool Polygon::conflict(const Path &path) const
	{
		return std::find(_paths.begin(), _paths.end(), path) != _paths.end();
	}

	// ある多角形が何点で多角形に衝突しているかどうか
	unsigned int Polygon::conflict(const Polygon &poly) const
	{
		unsigned int sum = 0;

		for (const auto & path : poly._paths)
		{
			if (conflict(path))
				sum++;
		}

		return sum;
	}

	// +状ならtrueを返す．
	bool Polygon::plusConflict(uint8_t x, uint8_t y) const
	{
		int count = 0;

		for (int i = 0; i < 4; i++)
		{
			auto testCases = Path::squareNeighborPath(x, y, (Position)i);
			bool flag = false;

			for (auto & testCase : testCases)
			{
				if (std::find(_paths.begin(), _paths.end(), testCase) != _paths.end())
				{
					flag = true;
					break;
				}
			}

			count += flag ? 1 : 0;
		}

		return count >= 2;
	}

	// 多角形の内部にある置ける領域の数
	unsigned int Polygon::polygonCount() const
	{
		unsigned int sum = 0;

		for (const auto &child : _children)
			sum += child.polygonCount();

		return sum + (_isEmpty ? 1 : 0);
	}

	bool Polygon::operator==(const Polygon &poly) const
	{
			return
					_paths == poly._paths &&
					_children == poly._children &&
					_isEmpty == poly._isEmpty;
	}
}
