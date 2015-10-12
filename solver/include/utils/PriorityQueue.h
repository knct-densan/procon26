#pragma once

#include <queue>
#include <algorithm>

namespace solver
{
	template <typename T, typename Tcon>
	class PriorityQueue : public std::priority_queue<T, Tcon>
	{
	public:
		void resize(size_t size)
		{
			assert(size < c.size());

			std::sort(c.begin(), c.end());
			c.erase(c.begin() + size, c.end());
			std::make_heap(c.begin(), c.end());
		}
	};
}