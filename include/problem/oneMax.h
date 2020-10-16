///
/// @file oneMax.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef EVALONEMAX_H
#define EVALONEMAX_H

#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <unistd.h>

#include "../solution/solution.h"
#include "../solutionSelection/maximization.h"
#include "../solutionSelection/solutionSelection.h"

#include "problem.h"

namespace stocos {

using TYPE_FITNESS_ONEMAX = unsigned int;
using TYPE_CELL_ONEMAX = bool;
using SOL_ONEMAX = Solution<TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>;
class OneMax : public Problem<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> {
  public:
	OneMax();

	OneMax(const std::string& fileInstance);

	OneMax(unsigned int N);

	~OneMax();

	virtual void loadJson(const Json::Value& config);

	std::unique_ptr<SOL_ONEMAX> new_solution() const;

	bool checkSolutionStructure(const SOL_ONEMAX& s) const;
	void evaluation(SOL_ONEMAX& s);

	// void incremental(const Solution &s, unsigned int mutatedCell) const;

	void resetSolution(SOL_ONEMAX& s) const;

	TYPE_FITNESS_ONEMAX getFitnessObjectif(unsigned int numObjectif = 0) const;

	bool solutionSelection(const SOL_ONEMAX& s_worst, const SOL_ONEMAX& s_best);

	unsigned int solutionSelection(const Population<SOL_ONEMAX>& p);

  private:
	Maximization<SOL_ONEMAX> solution_selection;
	std::string instance_number;
	unsigned int _N;
};

} // namespace stocos
#endif