///
/// @file simulatedAnnealing.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef SIMULATEDANNELING_H
#define SIMULATEDANNELING_H

#include <memory>
#include <random>
#include <string>

#include "../../problem/problem.h"
#include "../../statistic/statistic.h"
#include "../../stoppingCriteria/stoppingCriteria.h"
#include "operator/atomicOperation.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class SimulatedAnnealing : public Optimization<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
    SimulatedAnnealing(
        std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations);
    virtual ~SimulatedAnnealing();

    std::unique_ptr<SOL> operator()(const SOL& s);
    std::string className() const;

    void className(const std::string& class_name);

  protected:
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
    std::string _class_name;

    SOL solution_star;
};

} // namespace stocos
#endif