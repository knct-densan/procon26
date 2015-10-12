#include <string>
#include <cassert>
#include "../../include/utils/Util.h"
#include "../../include/utils/ProblemLoader.h"


namespace solver
{
	bool ProblemLoader::run(
		Map &map,
		std::unique_ptr<Stone[]> &stones,
		int &stoneCount,
		std::istream &ifs
		)
	{
		std::string line;

		debug_output("start ProblemLoader");

		// read Map
		for (int y = 0; y < 32; y++)
		{
			solver::getline(ifs, line);
			assert(line != "");

			for (int x = 0; x < 32; x++)
			{
				auto &stoneStatus = map.set(x, y);
				if (line[x] == '1')
				{
					stoneStatus = Status::OBSTACLE;
					map.evalStone(x, y);
				}
				else
				{
					stoneStatus = Status::EMPTY;
				}
			}
		}

		// skip blank
		solver::getline(ifs, line);
		assert(line == "");

		// get StoneCount
		ifs >> stoneCount;

		// skip stoneCount's CRLF
		solver::getline(ifs, line);
		assert(line == "");

		assert(1 <= stoneCount && stoneCount <= 256);

		stones.reset(new Stone[stoneCount]);

		// read Stone
		for (int i = 0; i < stoneCount; i++)
		{
			for (int y = 0; y < 8; y++)
			{
				solver::getline(ifs, line);
				for (int x = 0; x < 8; x++)
					stones[i].set(x, y) = line[x] == '1' ? Status::STONE : Status::EMPTY;
			}
			if (i != stoneCount - 1)
			{
				// skip blank-line
				solver::getline(ifs, line);
				assert(line == "");
			}
		}

		for (int i = 0; i < stoneCount; i++)
			stones[i].setup();

		debug_output("finish ProblemLoader");

		return true;
	}
}