///
/// @file magicSequence.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief magic sequence Problem
///

#ifndef MAGICSEQUENCE_H
#define MAGICSEQUENCE_H

#include "../solution/solution.h"
#include "../solutionSelection/maximization.h"
#include "problem.h"

namespace stocos {

using TYPE_FITNESS_MAGICSEQUENCE = double;
using TYPE_CELL_MAGICSEQUENCE = unsigned int;
using SOL_MAGICSEQUENCE = Solution<TYPE_FITNESS_MAGICSEQUENCE, TYPE_CELL_MAGICSEQUENCE>;
class MagicSequence
    : public Problem<SOL_MAGICSEQUENCE, TYPE_FITNESS_MAGICSEQUENCE, TYPE_CELL_MAGICSEQUENCE> {
  public:
    MagicSequence();

    void loadJson(const Json::Value& config);

    void evaluation(SOL_MAGICSEQUENCE& s);

    // void incremental(const Solution &s, unsigned int mutatedCell) const;

    void resetSolution(SOL_MAGICSEQUENCE& s) const;

    bool solutionSelection(const SOL_MAGICSEQUENCE& s_worst, const SOL_MAGICSEQUENCE& s_best);

    unsigned int solutionSelection(const Population<SOL_MAGICSEQUENCE>& p);

  private:
    Maximization<SOL_MAGICSEQUENCE> solution_selection;
};

} // namespace stocos
#endif