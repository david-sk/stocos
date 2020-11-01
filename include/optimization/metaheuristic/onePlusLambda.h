///
/// @file onePlusLambda.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef ONEPLUSLAMBDA_H
#define ONEPLUSLAMBDA_H

#include <memory>
#include <random>
#include <string>

#include "../../problem/problem.h"
#include "../../statistic/statistic.h"
#include "../../stoppingCriteria/stoppingCriteria.h"
#include "../optimization.h"
#include "operator/atomicOperation.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class OnePlusLambda : public Optimization<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
    OnePlusLambda(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
                  std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
                  std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
                  std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations,
                  unsigned int lambda);

    ~OnePlusLambda();

    std::unique_ptr<SOL> operator()(const SOL& s);

    std::string className() const;

    void className(const std::string& class_name);

  protected:
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
    unsigned int _lambda;
    std::string _class_name;
    SOL solution_star;
    SOL solution_alpha;
    SOL solution_beta;
};

} // namespace stocos
#endif