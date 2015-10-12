#include "../../include/utils/Point.h"

namespace solver
{
	size_t hash_value(const Point &obj)
	{
		assert(-8 <= obj._x && obj._x <= 39 && -8 <= obj._y && obj._y <= 39);
		return (obj._x + 8) * 48 + (obj._y + 8);
	}
}
