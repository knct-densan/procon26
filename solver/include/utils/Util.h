#pragma once

#include <istream>
#include <string>
#include <cassert>
#include <cstdint>
#include <vector>
#include <array>
#include <algorithm>

#define ALL(a)  (a).begin(),(a).end()

namespace solver
{
	const int EVALER_NUM = 6;
	typedef uint64_t HASH_TYPE;

	enum Direction : uint8_t
	{
		UL = 0, // Up-Left is origin 0
		UR = 1, // Up-Right 90
		DR = 2, // Down-Right 180
		DL = 3 // Down-Left 270
	};

	typedef Direction Position;

	enum Status : uint8_t
	{
		EMPTY = 0,
		OBSTACLE = 1,
		STONE = 2,
		NEIGHBOR = 3
	};

	const std::array< std::pair<int, int>, 4> neighborChords =
	{
		std::make_pair(1, 0),
		std::make_pair(0, 1),
		std::make_pair(-1, 0),
		std::make_pair(0, -1)
	};

	void debug_output(std::string &msg);

	void debug_output(const char *msg);

	void getline(std::istream &ifs, std::string &line);

	std::string StatusToString(Status status);

	template<typename T> T bitReverse(T data)
	{
		T result = 0;

		for (unsigned int i = 0; i < sizeof(data) * 8; i++)
		{
			result <<= 1;
			result += bitAt(i, data);
		}

		return result;
	}

	template<typename T>
	T bitAt(int pos, T data)
	{
		assert(0 <= pos && pos < sizeof(T) * 8);

		return (data >> pos) & 1;
	}

	template<typename T>
	bool remove(std::vector<T> &container, const T& target)
	{
		auto it = std::find(ALL(container), target);

		if (it != container.end())
		{
			container.erase(it);
			return true;
		}
		else
		{
			return false;
		}
	}

	template<class InputIterator, typename T>
	bool contain(InputIterator begin, InputIterator end, const T& target)
	{
		auto it = std::find(begin, end, target);

		return it != end;
	}

	static const std::string endl = "\r\n";

}
