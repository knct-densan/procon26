#include <sstream>
#include "../include/utils/Util.h"
#include "../include/Place.h"

namespace solver
{
	std::string Place::toString() const
	{
		if (_skip)
			return solver::endl;
		else
			return
				std::to_string(_x) + " " +
				std::to_string(_y) + " " +
				(_up ? "H" : "T") + " " +
				std::to_string(_dir * 90) + solver::endl;
	}
}