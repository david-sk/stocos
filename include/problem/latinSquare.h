///
/// @file latinSquare.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef EVALLATINSQUARE_H
#define EVALLATINSQUARE_H

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

using TYPE_FITNESS_LATINSQUARE = unsigned int;
using TYPE_CELL_LATINSQUARE = bool;
using SOL_LATINSQUARE = Solution<TYPE_FITNESS_LATINSQUARE, TYPE_CELL_LATINSQUARE>;
class LatinSquare
    : public Problem<SOL_LATINSQUARE, TYPE_FITNESS_LATINSQUARE, TYPE_CELL_LATINSQUARE> {
  public:
    LatinSquare();

    LatinSquare(const std::string& fileInstance);

    LatinSquare(unsigned int N);

    ~LatinSquare();

    virtual void loadJson(const Json::Value& config);
    std::unique_ptr<SOL_LATINSQUARE> new_solution() const;

    bool checkSolutionStructure(const SOL_LATINSQUARE& s) const;

    void evaluation(SOL_LATINSQUARE& s);

    // void incremental(const Solution &s, unsigned int mutatedCell) const;

    void resetSolution(SOL_LATINSQUARE& s) const;

    TYPE_FITNESS_LATINSQUARE getFitnessObjectif(unsigned int numObjectif = 0) const;

    bool solutionSelection(const SOL_LATINSQUARE& s_worst, const SOL_LATINSQUARE& s_best);

    unsigned int solutionSelection(const Population<SOL_LATINSQUARE>& p);

  private:
    Maximization<SOL_LATINSQUARE> solution_selection;
    std::string instance_number;
    unsigned int _N;
};

} // namespace stocos
#endif