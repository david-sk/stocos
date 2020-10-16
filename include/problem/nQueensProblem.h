///
/// @file nQueensProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2020-10
/// @brief Definition of the n-queens problem
///        see: http://www.csplib.org/Problems/prob054/
///

#ifndef EVALNQUEENSPROBLEM_H
#define EVALNQUEENSPROBLEM_H

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

using TYPE_FITNESS_NQUEENSPROBLEM = unsigned int;
using TYPE_CELL_NQUEENSPROBLEM = unsigned int;
using SOL_NQUEENSPROBLEM = Solution<TYPE_FITNESS_NQUEENSPROBLEM, TYPE_CELL_NQUEENSPROBLEM>;
class NQueensProblem
	: public Problem<SOL_NQUEENSPROBLEM, TYPE_FITNESS_NQUEENSPROBLEM, TYPE_CELL_NQUEENSPROBLEM> {
  public:
	NQueensProblem();

	NQueensProblem(const std::string& fileInstance);

	NQueensProblem(unsigned int n);

	~NQueensProblem();

	virtual void loadJson(const Json::Value& config);

	std::unique_ptr<SOL_NQUEENSPROBLEM> new_solution() const;

	bool checkSolutionStructure(const SOL_NQUEENSPROBLEM& s) const;

	// Gives the number of queens without fail with another queen
	void evaluation(SOL_NQUEENSPROBLEM& s);

	void resetSolution(SOL_NQUEENSPROBLEM& s) const;

	TYPE_FITNESS_NQUEENSPROBLEM getFitnessObjectif(unsigned int numObjectif = 0) const;

	bool solutionSelection(const SOL_NQUEENSPROBLEM& s_worst, const SOL_NQUEENSPROBLEM& s_best);

	unsigned int solutionSelection(const Population<SOL_NQUEENSPROBLEM>& p);

	bool evaluationSubSolution(SOL_NQUEENSPROBLEM& s) const;
	bool check_diagonal(const SOL_NQUEENSPROBLEM& solution) const;
	bool check_line(const SOL_NQUEENSPROBLEM& solution) const;

  private:
	Maximization<SOL_NQUEENSPROBLEM> solution_selection;
	std::string instance_number;
	unsigned int _n;
};

} // namespace stocos
#endif