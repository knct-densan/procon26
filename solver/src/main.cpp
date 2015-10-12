#include <iostream>
#include <fstream>
#include <cassert>
#include <ctime>
#include "../include/Problem.h"
#include "../include/Solver.h"
#include "../include/Answer.h"
#include "../include/Hasher.h"

int main(int argc, char *argv[])
{
	// executeName inputName + outputName + bestFirst + beam + params
	if (argc == 1 + 1 + 1 + 1 + 1 + solver::EVALER_NUM)
	{
		// inputName
		std::ifstream ifs(argv[1]);
		assert(ifs.good());
		auto prob = solver::Problem(ifs);

		std::ofstream ofs(argv[2], std::ofstream::binary);
		assert(ofs.good());

		// beam-search mode
		bool bestFirst;
		int beamModeNum = std::stoi(argv[3]);
		if (beamModeNum == 0)
			bestFirst = false;
		else
			bestFirst = true;

		// beam
		int beam = std::stoi(argv[4]);
		solver::Solver::setup(beam, bestFirst);

		// params
		std::vector<int> params;
		params.resize(solver::EVALER_NUM);
		for (int i = 0; i < solver::EVALER_NUM; i++)
			params[i] = std::stoi(argv[5 + i]);
		solver::Evaler::setup(prob);
		solver::Answer::setup(params);

		// run
//		std::cout << prob._stoneCount << std::endl;
		auto result = solver::Solver::Solve(prob);
		std::cout << (1024 - result.zk()) * 257 + result.used() << std::endl;
//		std::cout << result._map.dump();
		ofs << result.getAnswer();
	}
	else
		std::cout << std::numeric_limits<int>::max << std::endl;
	
	/*
	// inputName
	std::ifstream ifs("problem.txt");
	assert(ifs.good());
	auto prob = solver::Problem(ifs);

	// beam-search mode
	bool bestFirst;
	int beamModeNum = 0;
	if (beamModeNum == 0)
		bestFirst = false;
	else
		bestFirst = true;

	// beam
	int beam = 50;
	solver::Solver::setup(beam, bestFirst);

	// params
	std::vector<int> params;
	params.resize(solver::EVALER_NUM);
//	for (int i = 0; i < solver::EVALER_NUM; i++)
//		params[i] = std::stoi(argv[4 + i]);
	params = { -2, 4, 1, 3, -5, 6 };
	solver::Evaler::setup(prob);
	solver::Answer::setup(params);

	// run
	std::cout << prob._stoneCount << std::endl;
	solver::Solver::Solve(prob);	
	*/
	
	return 0;
}