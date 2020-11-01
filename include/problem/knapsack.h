///
/// @file knapsack.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief Knapsack Problem
///

#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <map>
#include <unistd.h>
#include <utility>
#include <vector>

#include <jsoncpp/json/json.h>

#include "../solution/solution.h"
#include "../solutionSelection/maximization.h"
#include "problem.h"

namespace stocos {

using TYPE_FITNESS_KNAPSACK = int;
using TYPE_CELL_KNAPSACK = bool;
using SOL_KNAPSACK = Solution<TYPE_FITNESS_KNAPSACK, TYPE_CELL_KNAPSACK>;

class Knapsack : public Problem<SOL_KNAPSACK, TYPE_FITNESS_KNAPSACK, TYPE_CELL_KNAPSACK> {
  public:
    Knapsack();

    Knapsack(const std::string& fileInstance);

    ~Knapsack();

    void loadJson(const Json::Value& config);

    void evaluation(SOL_KNAPSACK& s);

    // void incremental(const Solution &s, unsigned int mutatedCell) const;

    void resetSolution(SOL_KNAPSACK& s) const;

    std::unique_ptr<SOL_KNAPSACK> new_solution() const;

    unsigned int sizeArraySolution() const;

    TYPE_FITNESS_KNAPSACK getFitnessObjectif(unsigned int numObjectif = 0) const;

    bool solutionSelection(const SOL_KNAPSACK& s_worst, const SOL_KNAPSACK& s_best);
    unsigned int solutionSelection(const Population<SOL_KNAPSACK>& p);

  private:
    Maximization<SOL_KNAPSACK> solution_selection;
    std::string instance_number;
    int capacity;
    unsigned int nbItems;
    std::vector<int> weight;
    std::vector<int> profit;
    int fitnessObjectif;
};

} // namespace stocos

#endif