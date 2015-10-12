#include "../include/Polygons.h"
#include "../include/utils/Util.h"

#include <iterator>
#include <queue>

namespace solver
{
	Polygons::Polygons(const Map &map)
	{
		Polygon mapPolygon;

		// path from (0, 0) to (0, 32)
		for (int i = 0; i < 32; i++)
		{
			Point start = { (int8_t)0, (int8_t)i };
			Point end = { (int8_t)0, (int8_t)(i + 1) };

			Path newPath = { start, end };

			mapPolygon._paths.push_back(newPath);
		}

		// path from (0, 32) to (32, 32)
		for (int i = 0; i < 32; i++)
		{
			Point start = { (int8_t)i, (int8_t)32 };
			Point end = { (int8_t)(i + 1), (int8_t)32 };

			Path newPath = { start, end };

			mapPolygon._paths.push_back(newPath);
		}

		// path from (32, 32) to (32, 0)
		for (int i = 31; i >= 0; i--)
		{
			Point start = { (int8_t)32, (int8_t)(i + 1) };
			Point end = { (int8_t)32, (int8_t)i };

			Path newPath = { start, end };

			mapPolygon._paths.push_back(newPath);
		}

		// path from (32, 0) to (0, 0)
		for (int i = 31; i >= 0; i--)
		{
			Point start = { (int8_t)(i + 1), (int8_t)0 };
			Point end = { (int8_t)i, (int8_t)0 };

			Path newPath = { start, end };

			mapPolygon._paths.push_back(newPath);
		}

		mapPolygon._isEmpty = true;
		_area = 32 * 32;

		_children.push_back(mapPolygon);

		for (int y = 0; y < 32; y++)
		{
			for (int x = 0; x < 32; x++)
			{
				if (map.get(x, y) == Status::OBSTACLE)
					applyStone(x, y);
			}
		}
	}

	// (x, y)座標に石を置く時に呼ぶメソッド
	bool Polygons::applyStone(uint8_t x, uint8_t y)
	{
		Polygon newStone(x, y);

		decltype(&_children) children = nullptr;
		auto master = &_children;
		Polygon *parent = nullptr;
		Polygon *grandparent = nullptr;

		std::queue<Polygon *> q;

		for (auto &poly : *master)
			q.push(&poly);

		while (!q.empty())
		{
			auto &poly = q.front();
			q.pop();

			if (poly->contain(newStone))
			{
				grandparent = parent;
				parent = poly;
				children = &poly->_children;
				if (parent != nullptr)
					master = &parent->_children;
				for (auto &child : *children)
					q.push(&child);
			}
		}

		std::vector<Polygon *> conflicts;
		unsigned int conflictCount = 0;

		for (auto & poly : *children)
		{
			unsigned int nowConflict = poly.conflict(newStone);
			if (nowConflict > 0)
			{
				conflicts.push_back(&poly);
			}
			conflictCount += nowConflict;
		}

		if (conflicts.size() == 0)
		{
			// 自結合 or 新規( or plusConflict)

			// 親がいない場合
			if (parent == nullptr)
			{
				// 新規
				newStone._isEmpty = false;
				master->push_back(newStone);
			}
			else
			{
				if (parent->conflict(newStone) > 0)
				{
					// 自結合( or plusConflict)
					auto results = merge(x, y, *parent);
					for (auto &child : parent->_children)
					{
						auto flag = false;
						for (auto &result : results)
						{
							if (result.contain(child))
							{
								result._children.push_back(child);
								flag = true;
								break;
							}
						}
						assert(flag);
					}

					Polygon parentData = *parent;

					for (auto &result : results)
					{
						result._isEmpty = parent->_isEmpty;
						if (grandparent != nullptr)
							grandparent->_children.push_back(result);
						else
							_children.push_back(result);
					}

					if (grandparent != nullptr)
						assert(remove(grandparent->_children, parentData));
					else
						assert(remove(_children, parentData));
				}
				else
				{
					// 新規
					newStone._isEmpty = false;
					master->push_back(newStone);
				}
			}
		}
		else
		{
			// 他結合 or 自他結合
			if (parent != nullptr && parent->conflict(newStone) > 0)
			{
				// 自他結合
				std::list<Polygon> polys;
				polys.push_back(*parent);
				for (auto conflict : conflicts)
					polys.push_back(*conflict);
				auto results = merge(x, y, polys);
				assert(results.size() == 1);
				auto result = *results.begin();
				result._isEmpty = true;

				// 内部の子を外に追い出す
				for (auto &conflict : conflicts)
				{
					if (grandparent != nullptr)
					{
						grandparent->_children.insert(
							grandparent->_children.end(),
							ALL(conflict->_children)
							);
					}
					else
					{
						_children.insert(
							_children.end(),
							ALL(conflict->_children)
							);
					}
				}

				// parent内のinternalを削除
				std::vector<Polygon> polyData;
				for (auto &conflict : conflicts)
					polyData.push_back(*conflict);

				for (auto &conflict : polyData)
					assert(remove(*master, conflict));

				// parentの子をresult内に移す
				result._children.insert(
					result._children.end(),
					ALL(*master)
					);

				Polygon parentData = *parent;

				// resultを追加する
				if (grandparent != nullptr)
				{
					for (auto & result : results)
						grandparent->_children.push_back(result);
				}
				else
				{
					for (auto & result : results)
						_children.push_back(result);

				}

				// parentを削除する
				if (grandparent != nullptr)
					assert(remove(grandparent->_children, parentData));
				else
					assert(remove(_children, parentData));
			}
			else
			{
				// 他結合
				auto polys = std::list<Polygon>();

				for (auto conflict : conflicts)
					polys.push_back(*conflict);

				auto results = merge(x, y, polys);
				assert(results.size() == 1);
				auto result = *results.begin();
				result._isEmpty = false;

				for (auto &conflict : conflicts)
				{
					for (auto child : conflict->_children)
						result._children.push_back(child);
				}

				std::vector<Polygon> polyData;
				for (auto &conflict : conflicts)
					polyData.push_back(*conflict);

				for (auto &conflict : polyData)
					assert(remove(*master, conflict));

				master->push_back(result);
			}
		}
		_area--;
		return true;
	}

	unsigned int Polygons::area() const
	{
		return _area;
	}

	unsigned int Polygons::polygonCount() const
	{
		unsigned int polygonCount = 0;

		for (const auto &child : _children)
		{
			polygonCount += child.polygonCount();
		}

		return polygonCount;
	}

	unsigned int Polygons::perimeter() const
	{
		unsigned int perimeter = 0;

		for (const auto &child : _children)
		{
			perimeter += child.perimeter();
		}

		return perimeter;
	}

	double Polygons::averageEmpty() const
	{
		// 平均閑散度 := 面積 / 多角形の数
		// 大きいほど多角形1つあたりの面積が大きい

		return (double)_area / (double)polygonCount();
	}

	double Polygons::complextity() const
	{
		// 多角形複雑度 := 面積 / 周長
		// 大きいほど単純

		return (double)_area / (double)perimeter();
	}

	std::list<Polygon> Polygons::merge(
		int8_t x,
		int8_t y,
		const std::list<Polygon> &polys) const
	{
		bool usableSquarePath[4];
		auto squarePath = Path::squarePath(x, y);

		for (int i = 0; i < 4; i++)
		{
			bool flag = false; // contain flag
			for (auto &poly : polys)
			{
				auto it = std::find(ALL(poly._paths), squarePath[i]);
				if (it != poly._paths.end())
				{
					flag = true;
					break;
				}
			}
			usableSquarePath[i] = !flag; // if contain => cannot use
		}

		bool usableNeighborPath[8]; // 近傍
		auto neighborPath = Path::squareNeighborPath(x, y);

		for (int i = 0; i < 8; i++)
		{
			bool flag = false;
			for (int j = 0; j < 4; j++)
			{
				if (usableSquarePath[j] && neighborPath[i].connectable(squarePath[j]))
				{
					flag = true;
					break;
				}
			}
			usableNeighborPath[i] = flag;
		}

		std::list<std::vector<Path>> loops;

		std::vector<Path> paths;
		for (auto &poly : polys)
			paths.insert(paths.end(), ALL(poly._paths));
		
		for (int i = 0; i < 4; ++i)
		{
			if (!usableSquarePath[i])
				while (remove(paths, squarePath[i]));
		}
		

		/*
		for (int i = 0; i < 8; ++i)
		{
		if (!usableNeighborPath[i])
		while (remove(paths, neighborPath[i]));
		}
		*/

		while (paths.size() != 0)
			loops.push_back(makeLoop(x, y, paths, usableNeighborPath));

		assert(decideSquarePath(loops, x, y, usableSquarePath));

		std::list<Polygon> result;

		for (auto &loop : loops)
			result.emplace_back(loop);

		if (result.size() == 2)
		{
			bool flag = false;
			for (auto itx = result.begin(); itx != result.end() && !flag; ++itx)
			{
				for (auto ity = result.begin(); ity != result.end() && !flag; ++ity)
				{
					if (itx != ity)
					{
						if (itx->contain(*ity))
						{
							itx->_children.push_back(*ity);
							itx->_children.back()._isEmpty = true;
							result.remove(*ity);
							flag = true;
						}
					}
				}
			}
		}

		return result;

	}
	
	bool Polygons::connectable(const std::vector<Path> &first, const std::vector<Path> &second) const
	{
		auto &front = first.front();
		auto &end = first.back();

		if (front.connectable(second.front()))
			return true;

		if (front.connectable(second.back()))
			return true;

		if (end.connectable(second.front()))
			return true;

		if (end.connectable(second.back()))
			return true;

		return false;
	}

	void Polygons::connect(std::vector<Path> &first, std::vector<Path> &second) const
	{
		auto &front = first.front();
		auto &end = first.back();

		if (front.connectable(second.front()))
		{
			std::reverse(ALL(first));
			for (auto & path : first)
				path = path.reverse();
			return connect(first, second);
		}

		if (front.connectable(second.back()))
		{
			std::reverse(ALL(first));
			for (auto & path : first)
				path = path.reverse();
			return connect(first, second);
		}

		if (end.connectable(second.front()))
		{
			for (const auto &path : second)
				first.push_back(first.back().connectable(path));
			return;
		}

		if (end.connectable(second.back()))
		{
			std::reverse(ALL(second));
			for (auto & path : second)
				path = path.reverse();
			return connect(first, second);
		}
	}

	std::list<Polygon> Polygons::merge(
		int8_t x,
		int8_t y,
		const Polygon &poly) const
	{
		std::list<Polygon> polys;
		polys.push_back(poly);

		return merge(x, y, polys);
	}

#define normalize(i) ((i + paths.size()) % paths.size())
#define pathAt(i) (paths[normalize(i)])

	std::vector<Path> Polygons::makeLoop(int8_t x, int8_t y, std::vector<Path> &paths, const bool usableSquareFlag[8]) const
	{
		auto neighborPath = Path::squareNeighborPath(x, y);
		auto squarePath = Path::squarePath(x, y);
		std::vector<Path> usablePath;
		std::vector<Path> result;
		std::vector<int> removeList;
		removeList.reserve(paths.size());

		int startIt = -1;

		for (int i = 0; i < 8; i++)
			if (usableSquareFlag[i])
				usablePath.push_back(neighborPath[i]);

		for (const auto &path : usablePath)
		{
			auto it = std::find(ALL(paths), path);
			if (it != paths.end())
			{
				startIt = it - paths.begin();
				break;
			}
		}

		assert(startIt != -1);

		removeList.push_back(startIt);
		auto start = paths[startIt];
		if (contain(ALL(squarePath), start._start))
		{
			// start pos is part of square
			result.push_back(start);
		}
		else
		{
			// end pos is part of square
			result.push_back(start.reverse());
		}

		while (removeList.size() != paths.size())
		{
			bool found = false;
			bool finish = false;
			for (int i = 0; i < paths.size(); i++)
			{
				if (!contain(ALL(removeList), i))
				{
					auto path = result.back().connectable(paths[i]);
					if (path)
					{
						removeList.push_back(i);
						result.push_back(path);
						found = true;

						if (contain(ALL(usablePath), path))
						{
							finish = true;
						}

						break;
					}
				}
			}
			assert(found);
			if (finish)
				break;
		}

		std::vector<Path> param;
		param.reserve(paths.size() - removeList.size());
		for (int i = 0; i < paths.size(); i++)
			if (!contain(ALL(removeList), i))
				param.push_back(paths[i]);

		paths = param;

		assert(contain(ALL(usablePath), result.front()));
		assert(contain(ALL(usablePath), result.back()));

		return result;
	}

#undef pathAt
#undef normalize

	bool Polygons::decideSquarePath(
		std::list<std::vector<Path>> &loops,
		int8_t x,
		int8_t y,
		bool usableSquarePath[4]) const
	{
		if (_decideSquarePath(loops, x, y, true, usableSquarePath))
			return true;
		else if (_decideSquarePath(loops, x, y, false, usableSquarePath))
			return true;

		return false;
	}

	bool Polygons::_decideSquarePath(
		std::list<std::vector<Path>> &loops,
		int8_t x,
		int8_t y,
		bool clockwise,
		bool usableSquarePath[4]) const
	{
		bool status[4];
		for (int i = 0; i < 4; i++)
			status[i] = usableSquarePath[i];

		if (loops.size() == 0)
			return true;

		auto &loop = loops.front();

		auto start = loop.front()._start;
		auto end = loop.back()._end;

		assert(isPointSquare(x, y, start));
		assert(isPointSquare(x, y, end));

		auto startPos = pointToPosition(x, y, start);
		auto endPos = pointToPosition(x, y, end);

		auto paths = makePath(x, y, endPos, startPos, clockwise);

		for (auto &path : paths)
		{
			auto key = pathToSquarePathId(x, y, path);
			assert(0 <= key && key < 4);
			if (!status[key])
				return false;
			else
				status[key] = false;
		}

		std::list<std::vector<Path>> newloops(std::next(loops.begin()), loops.end());

		if (!_decideSquarePath(newloops, x, y, true, status))
			if (!_decideSquarePath(newloops, x, y, false, status))
				return false;

		loops.erase(std::next(loops.begin()), loops.end());
		loops.insert(loops.end(), ALL(newloops));

		for (auto &path : paths)
			loop.push_back(path);

		return true;
	}

	std::list<Path> Polygons::makePath(
		int8_t x,
		int8_t y,
		Position start,
		Position end,
		bool clockwise
		) const
	{
		std::list<Path> result;
		Path nowPath;
		Position next = start;

		while (next != end)
		{
			if (clockwise)
			{
				switch (next)
				{
				case Position::UL:
					nowPath = Path(Point(x, y), Point(x + 1, y));
					next = Position::UR;
					break;
				case Position::UR:
					nowPath = Path(Point(x + 1, y), Point(x + 1, y + 1));
					next = Position::DR;
					break;
				case Position::DR:
					nowPath = Path(Point(x + 1, y + 1), Point(x, y + 1));
					next = Position::DL;
					break;
				case Position::DL:
					nowPath = Path(Point(x, y + 1), Point(x, y));
					next = Position::UL;
					break;
				}
			}
			else
			{
				switch (next)
				{
				case Position::UL:
					nowPath = Path(Point(x, y), Point(x, y + 1));
					next = Position::DL;
					break;
				case Position::UR:
					nowPath = Path(Point(x + 1, y), Point(x, y));
					next = Position::UL;
					break;
				case Position::DR:
					nowPath = Path(Point(x + 1, y + 1), Point(x + 1, y));
					next = Position::UR;
					break;
				case Position::DL:
					nowPath = Path(Point(x, y + 1), Point(x + 1, y + 1));
					next = Position::DR;
					break;
				}
			}
			result.push_back(nowPath);
		}

		return result;
	}

	Position Polygons::pathToPosition(int8_t x, int8_t y, Path path) const
	{
		Point point;
		if (isPointSquare(x, y, path._start))
		{
			point = path._start;
		}
		else if (isPointSquare(x, y, path._end))
		{
			point = path._end;
		}

		assert(point != Point());

		return pointToPosition(x, y, point);
	}

	bool Polygons::isPointSquare(int8_t x, int8_t y, Point point) const
	{
		return
			(point._x == x || point._x == x + 1) &&
			(point._y == y || point._y == y + 1);
	}

	Position Polygons::pointToPosition(int8_t x, int8_t y, Point point) const
	{
		if (point._x == x && point._y == y)
			return Position::UL;

		if (point._x == x + 1 && point._y == y)
			return Position::UR;

		if (point._x == x && point._y == y + 1)
			return Position::DL;

		if (point._x == x + 1 && point._y == y + 1)
			return Position::DR;

		assert(false);
	}

	int8_t Polygons::pathToSquarePathId(int8_t x, int8_t y, Path path) const
	{
		if (path == Path(Point(x, y), Point(x, y + 1)))
			return 0;

		if (path == Path(Point(x, y + 1), Point(x + 1, y + 1)))
			return 1;

		if (path == Path(Point(x + 1, y + 1), Point(x + 1, y)))
			return 2;

		if (path == Path(Point(x + 1, y), Point(x, y)))
			return 3;

		return -1;
	}
}
