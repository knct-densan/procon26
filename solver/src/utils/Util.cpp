#include <iostream>
#include "../../include/utils/Util.h"

namespace solver
{
	void debug_output(std::string &msg)
	{
#ifdef _DEBUG
		if (msg != "")
		{
			if (msg[msg.size() - 1] == '\n')
				std::cerr << msg;
			else
				std::cerr << msg << std::endl;
		}
#endif
	}

	void debug_output(const char *msg)
	{
#ifdef _DEBUG
		debug_output(std::string(msg));
#endif
	}

	void getline(std::istream &ifs, std::string &line)
	{
		std::getline(ifs, line);

		if (line != "")
		{
			// remove CR from line
			if (line[line.size() - 1] == '\r')
				line.erase(line.size() - 1);

			// remove LF from line
			if (line[line.size() - 1] == '\n')
				line.erase(line.size() - 1);
		}

		debug_output(line);
	}

	std::string StatusToString(Status status)
	{
		switch (status)
		{
		case Status::EMPTY:
			return " ";
			break;

		case Status::OBSTACLE:
			return "X";
			break;

		case Status::STONE:
			return "S";
			break;

		case Status::NEIGHBOR:
			return "N";
			break;
		}

		return "";
	}
}