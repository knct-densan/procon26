#include <iostream>
#include <utility>
#include <functional>

#include <tbb/concurrent_vector.h>
#include <tbb/concurrent_unordered_set.h>

#include <tbb/parallel_sort.h>
#include <tbb/parallel_for_each.h>

#include "../include/Solver.h"
#include "../include/utils/Util.h"

namespace solver
{
	int Solver::_beam;
	int Solver::_maxQueueSize = 2000000;
	bool Solver::_bestFirst;
	
	Answer Solver::Solve(Problem &prob)
	{
		auto statuses = tbb::concurrent_vector<Answer>();
		auto nextStatuses = tbb::concurrent_vector<Answer>();
		auto hashTable = tbb::concurrent_unordered_set<Answer, std::hash<Answer>>();
		int maxZk = 0;
		int minUsed = 256;

		statuses.push_back(std::move(Answer(prob)));

		while (_bestFirst || statuses.front()._stoneCount != statuses.front()._places.size())
		{
			if (_bestFirst)
			{
				// 最良優先ビームサーチ
				// ハッシュテーブルが大きすぎる場合の処理
				if (hashTable.size() > _maxQueueSize)
				{
					tbb::concurrent_vector<Answer> tmp;
					tbb::concurrent_unordered_set<Answer, std::hash<Answer>> newHashTable;

					for (const auto & status : hashTable)
						tmp.push_back(status);

					tbb::parallel_sort(ALL(tmp), std::greater<Answer>());

					for (int i = 0; i < _maxQueueSize; i++)
						newHashTable.insert(tmp[i]);

					hashTable = std::move(newHashTable);
				}
			}
			else
			{
				// 幅優先ビームサーチ
				hashTable = tbb::concurrent_unordered_set<Answer, std::hash<Answer>>();
			}

			if (_beam < statuses.size())
			{
				tbb::parallel_sort(ALL(statuses), std::greater<Answer>());
				tbb::concurrent_vector<Answer> tmp;
				tmp.resize(_beam);

				for (int i = 0; i < _beam; i++)
					tmp[i] = statuses[i];

				statuses = std::move(tmp);
			}

			// 並列処理！
			tbb::parallel_for_each(ALL(statuses),
				[&](Answer &current)
			{
				auto next = current;
				if (statuses.front()._stoneCount != statuses.front()._places.size())
				{
					if (current.first())
					{
						for (int i = 0; i <= 1; i++) // up
						{
							for (int j = 0; j < 4; j++) // dir
							{
								for (int y = -7; y < 32; y++)
								{
									for (int x = -7; x < 32; x++)
									{
										if (next.applyPlacement(x, y, (bool)i, (Direction)j))
										{
											auto it = hashTable.find(next);
											if (it == hashTable.end())
											{
												hashTable.insert(next);
											}
											else
											{
												if (*it < next)
												{
													*it = next;
												}
											}
											next = current;
										}
									}
								}

							}
						}
					}
					else
					{
						auto &stone = current._stones[current._places.size()];
						for (int i = 0; i <= 1; i++) // up
						{
							for (int j = 0; j < 4; j++) // dir
							{
								bool alreadyPlaced[39][39];

								memset(alreadyPlaced, 0, sizeof(alreadyPlaced));
								for (auto stonePos : stone.stonePos((bool)i, (Direction)j))
									for (auto neighborPos : current._neighbors)
										alreadyPlaced[neighborPos._y - stonePos._y + 1 + 7][neighborPos._x - stonePos._x + 1 + 7] = true;

								for (int y = 0; y < 39; y++)
								{
									for (int x = 0; x < 39; x++)
									{
										if (alreadyPlaced[y][x])
										{
											if (next.applyPlacement(x - 7, y - 7, (bool)i, (Direction)j))
											{
												auto it = hashTable.find(next);
												if (it == hashTable.end())
												{
													hashTable.insert(next);
												}
												else
												{
													if (*it < next)
														*it = next;
												}
												next = current;
											}
										}
									}
								}
							}
						}
					}
					current.skipStone();
					nextStatuses.push_back(current);
				}
			});

			statuses = std::move(nextStatuses);

			for (auto status : hashTable)
			{
				if (_bestFirst)
				{
					if (status._stoneCount == status._places.size())
					{
						if (maxZk < status.zk())
						{
							maxZk = status.zk();
							minUsed = status.used();
//							int value = (1024 - status.zk()) * 257 + status.used();
//							std::cout << value << std::endl;
//							std::cout << status.getAnswer();
						}
						else if (maxZk == status.zk() && minUsed > status.used())
						{
							minUsed = status.used();
//							int value = (1024 - status.zk()) * 257 + status.used();
//							std::cout << value << std::endl;
//							std::cout << status.getAnswer();
						}
					}
				}
				statuses.push_back(std::move(status));
			}
		}

		Answer result;

		if (!_bestFirst)
		{
			int maxZk = 0;
			int minUsed = 256;

			for (const auto & status : statuses)
			{
				if (maxZk < status.zk())
				{
					maxZk = status.zk();
					minUsed = status.used();
					result = status;
				}
				else if (maxZk == status.zk() && minUsed > status.used())
				{
					minUsed = status.used();
					result = status;
				}
			}
//			int value = (1024 - result.zk()) * 257 + result.used();
//			std::cout << value << std::endl;
//			std::cout << result.getAnswer();
		}

		return result;
	}

	void Solver::setup(int beam, bool bestFirst)
	{
		_beam = beam;
		_bestFirst = bestFirst;
	}
}