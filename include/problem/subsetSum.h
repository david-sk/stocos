///
/// @file subsetSum.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief https://en.wikipedia.org/wiki/Subset_sum_problem
///

#ifndef EVALSUBSETSUM_H
#define EVALSUBSETSUM_H

#include <fstream>
#include <unistd.h>
#include <vector>

#include <jsoncpp/json/json.h>

#include "../solution/solution.h"
#include "problem.h"

namespace stocos {

using TYPE_FITNESS_SUBSETSUM = unsigned int;
using TYPE_CELL_SUBSETSUM = bool;
using SOL_SUBSETSUM = Solution<TYPE_FITNESS_SUBSETSUM, TYPE_CELL_SUBSETSUM>;
class Subsetsum : public Problem<SOL_SUBSETSUM, TYPE_FITNESS_SUBSETSUM, TYPE_CELL_SUBSETSUM> {
  public:
	Subsetsum();

	Subsetsum(const unsigned int N);

	Subsetsum(const std::string& fileInstance);

	void generateInstance(const unsigned int N);

	virtual ~Subsetsum();

	void loadJson(const Json::Value& config);

	TYPE_FITNESS_SUBSETSUM getFitnessObjectif(unsigned int numObjectif = 0) const;

	void evaluation(SOL_SUBSETSUM& s);

	// void incremental(const Solution &s, unsigned int mutatedCell) const;

	void resetSolution(SOL_SUBSETSUM& s) const;

	std::unique_ptr<SOL_SUBSETSUM> new_solution() const;

  private:
	std::vector<unsigned int> setOfNumbers;
	unsigned int fitnessObjectif;
};

} // namespace stocos

#endif