#include "../include/Evaler.h"
#include "../include/utils/Util.h"
#include <iostream>

namespace solver
{
	bool Evaler::_setup = false;
	std::vector<int> Evaler::_stoneAreaSum;

	void Evaler::setup(const Problem &prob)
	{
		_setup = true;

		auto stoneCount = prob._stoneCount;
		_stoneAreaSum.resize(stoneCount);

		_stoneAreaSum[stoneCount - 1] = prob._stones[stoneCount - 1].size();

		for (int i = stoneCount - 2; i >= 0; --i)
			_stoneAreaSum[i] = _stoneAreaSum[i + 1] + prob._stones[i].size();

	}

	double Evaler::eval(const Answer &answer, int type)
	{
		assert(0 <= type && type < EVALER_NUM);
		
		switch (type)
		{
		case 0:
			return placed(answer); // �u�����ʐ�
		case 1:
			return 256 - used(answer); // 256 - �g�����΂̐�
		case 2:
			return averageEmptyPerHoles(answer); // ��������̖ʐ�
		case 3:
			return averageEmptyPerPerimeter(answer); // ����������̖ʐ�
		case 4:
			return neighbors(answer); // �ߖT��
		case 5:
			return errorRemainingArea(answer); // �Ύc��ʐςƕ~�n�c��ʐς̌덷
		}

		return 0;
	}

	namespace EvalUtils
	{
#define OUT_OF_RANGE(x, y) (x < 0 || 32 <= x || y < 0 || 32 <= y)
		int checkEmpty(int startX, int startY, bool(&map)[32][32])
		{
			if (OUT_OF_RANGE(startX, startY) || map[startY][startX] == true)
				return 0;

			int emptySum = 1;
			map[startY][startX] = true;

			if (!OUT_OF_RANGE(startX + 1, startY) && !map[startY][startX + 1])
				emptySum += checkEmpty(startX + 1, startY, map);

			if (!OUT_OF_RANGE(startX, startY + 1) && !map[startY + 1][startX])
				emptySum += checkEmpty(startX, startY + 1, map);

			if (!OUT_OF_RANGE(startX - 1, startY) && !map[startY][startX - 1])
				emptySum += checkEmpty(startX - 1, startY, map);

			if (!OUT_OF_RANGE(startX, startY - 1) && !map[startY - 1][startX])
				emptySum += checkEmpty(startX, startY - 1, map);


			return emptySum;
		}
#undef OUT_OF_RANGE
	}

	int Evaler::placed(const Answer &answer)
	{
		// ���ɒu���ꂽ�΂̐���Ԃ�
		return answer.zk();
	}

	double Evaler::averageEmptyPerHoles(const Answer &answer)
	{
		// ���ϊՎU�x
		bool map[32][32];
		int emptySum = 0;
		int emptyPlaceSum = 0;

		for (int y = 0; y < 31; y++)
		{
			for (int x = 0; x < 31; x++)
			{
				switch (answer._map.get(x, y))
				{
				case Status::EMPTY:
					map[y][x] = false;
					break;
				case Status::NEIGHBOR:
					map[y][x] = false;
					break;
				case Status::OBSTACLE:
					map[y][x] = true;
					break;
				case Status::STONE:
					map[y][x] = true;
					break;
				}
			}
		}

		for (int y = 0; y < 31; y++)
		{
			for (int x = 0; x < 31; x++)
			{
				int sum = EvalUtils::checkEmpty(x, y, map);
				if (sum != 0)
				{
					emptySum += sum;
					emptyPlaceSum++;
				}
			}
		}

		return (double)emptySum / (double)emptyPlaceSum;
	}

	double Evaler::averageEmptyPerPerimeter(const Answer &answer)
	{
		return (double)(32 * 32 - answer.zk()) / (double)answer._map.perimeter();
	}

	int Evaler::errorRemainingArea(const Answer &answer)
	{
		// (�~�n�̎c��ʐ� - �΂̎c��ʐ�)^2
		return
			((32 * 32 - answer.zk()) - _stoneAreaSum[answer._places.size()]) *
			((32 * 32 - answer.zk()) - _stoneAreaSum[answer._places.size()]);
	}

	int Evaler::neighbors(const Answer &answer)
	{
		// �u����ꏊ�̐���Ԃ�(=�ߖT��)
		return answer._neighbors.size();
	}

	int Evaler::used(const Answer &answer)
	{
		// �g�p�����΂̐���Ԃ�
		return answer.used();
	}
}