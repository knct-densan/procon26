#pragma once

#include "Answer.h"
#include "utils/Util.h"

namespace solver
{
	class Hasher
	{
	public:
		static HASH_TYPE hash(const Answer &answer);

		static HASH_TYPE hash(
			const Answer &answer,
			const Place &place,
			const Stone &stone
			);


	private:
		static bool _first;
		static void makeHashTable();
		static HASH_TYPE hashTable[32][32][2];
		static HASH_TYPE statusToHash(int x, int y, const Status &status);
	};
}