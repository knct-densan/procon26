#include "../include/Path.h"

namespace solver
{	
	Path::operator bool() const
	{
		return _start != Point(0, 0) || _end != Point(0, 0);
	}

	bool Path::operator==(const Path& target) const
	{
		// ‹t•ûŒü‚Ì•Ó‚Íˆê’v‚Æ‚İ‚È‚·D

		return ((_start == target._start) && (_end == target._end)) ||
			((_start == target._end) && (_end == target._start));
	}

	bool Path::operator==(const Point& point) const
	{
		return _start == point || _end == point;
	}

	bool Path::isConnected(const Path& next) const
	{
		return _end == next._start;
	}

	Path Path::connectable(const Path& next) const
	{
			if (_end == next._start)
					return next;
			else if (_end == next._end)
					return next.reverse();
			else
					return Path(Point(0, 0), Point(0, 0));
	}

	Path Path::reverse() const
	{
		Path newPath(_end, _start);

		return newPath;
	}

	std::array<Path, 4> Path::squarePath(uint8_t x, uint8_t y)
	{
		std::array<Path, 4> result =
		{
			Path(Point(x, y), Point(x, y + 1)),
			Path(Point(x, y + 1), Point(x + 1, y + 1)),
			Path(Point(x + 1, y + 1), Point(x + 1, y)),
			Path(Point(x + 1, y), Point(x, y))
		};

		return result;
	}

	std::array<Path, 2> Path::squareNeighborPath(uint8_t x, uint8_t y, Position pos)
	{
		std::array<Path, 2> result;

		switch (pos)
		{
		case Position::UL:
			result[0] = Path(Point(x, y - 1), Point(x, y));
			result[1] = Path(Point(x - 1, y), Point(x, y));

			break;

		case Position::DL:
			result[0] = Path(Point(x - 1, y + 1), Point(x, y + 1));
			result[1] = Path(Point(x, y + 2), Point(x, y + 1));
			
			break;

		case Position::DR:
			result[0] = Path(Point(x + 1, y + 2), Point(x + 1, y + 1));
			result[1] = Path(Point(x + 2, y + 1), Point(x + 1, y + 1));
			
			break;

		case Position::UR:
			result[0] = Path(Point(x + 2, y), Point(x + 1, y));
			result[1] = Path(Point(x + 1, y - 1), Point(x + 1, y));

			break;
		}

		return result;
	}

	// (x, y)‚Ì³•ûŒ`‚ÉÚ‘±‚³‚ê‚é‘S•Ó‚ğ•Ô‚·
	std::array<Path, 8> Path::squareNeighborPath(uint8_t x, uint8_t y)
	{
			std::array<Path, 8> result =
			{
					Path(Point(x, y - 1), Point(x, y)),
					Path(Point(x - 1, y), Point(x, y)),
					Path(Point(x - 1, y + 1), Point(x, y + 1)),
					Path(Point(x, y + 2), Point(x, y + 1)),
					Path(Point(x + 1, y + 2), Point(x + 1, y + 1)),
					Path(Point(x + 2, y + 1), Point(x + 1, y + 1)),
					Path(Point(x + 2, y), Point(x + 1, y)),
					Path(Point(x + 1, y - 1), Point(x + 1, y))
			};

			return result;
	}
}