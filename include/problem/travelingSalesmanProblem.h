///
/// @file travelingSalesmanProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-07
/// @brief
///         instances : http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsplib.html
///

#ifndef EVALTRAVELINGSALESMANPROBLEM_H
#define EVALTRAVELINGSALESMANPROBLEM_H

#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include <jsoncpp/json/json.h>

#include "../solution/population.h"
#include "../solution/solution.h"
#include "../solutionSelection/minimization.h"
#include "problem.h"

namespace stocos {

using TYPE_FITNESS_STP = double;
using TYPE_CELL_STP = double;
using SOL_STP = Solution<TYPE_FITNESS_STP, TYPE_CELL_STP>;
class TravelingSalesmanProblem : public Problem<SOL_STP, TYPE_FITNESS_STP, TYPE_CELL_STP> {
  public:
    TravelingSalesmanProblem();

    TravelingSalesmanProblem(const std::string& fileInstance);

    virtual ~TravelingSalesmanProblem();

    void loadJson(const Json::Value& config);

    std::unique_ptr<SOL_STP> new_solution() const;

    bool checkSolutionStructure(const SOL_STP& s) const;

    void evaluation(SOL_STP& s);

    bool solutionSelection(const SOL_STP& s_worst, const SOL_STP& s_best);

    unsigned int solutionSelection(const Population<SOL_STP>& p);

  private:
    double distance_euclidienne(const std::pair<double, double>& node_a,
                                const std::pair<double, double>& node_b) const;

    Minimization<SOL_STP> solution_selection;
    std::string instance_number;
    unsigned int numberOfNodes;
    std::vector<std::pair<double, double>> nodes;
};

} // namespace stocos
#endif