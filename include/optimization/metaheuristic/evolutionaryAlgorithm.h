///
/// @file evolutionaryAlgorithm.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-06
/// @brief
///

#ifndef EVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGORITHM_H

#include <memory>
#include <random>
#include <string>

#include "../../problem/problem.h"
#include "../../solution/population.h"
#include "../optimization.h"
#include "operator/atomicOperation.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class EvolutionaryAlgorithm : public Optimization<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
    EvolutionaryAlgorithm(
        std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations,
        unsigned int mu = 50, unsigned int lambda = 50);

    ~EvolutionaryAlgorithm();

    std::unique_ptr<SOL> operator()(const SOL& s);
    std::string className() const;

    void className(const std::string& class_name);

  protected:
    std::unique_ptr<std::uniform_int_distribution<unsigned int>> rid_parents;
    std::unique_ptr<std::uniform_int_distribution<unsigned int>> rid_offsprings;
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
    std::string _class_name;
    SOL solution_star;
    Population<SOL> parents;
    Population<SOL> offsprings;
    unsigned int _mu;
    unsigned int _lambda;
};

} // namespace stocos
#endif
