///
/// @file bestImprovement.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef BESTIMPROVEMENT_H
#define BESTIMPROVEMENT_H

#include <memory>
#include <random>
#include <string>

#include "../../problem/problem.h"
#include "../../stoppingCriteria/stoppingCriteria.h"
#include "../optimizationAlgorithm.h"
#include "operator/atomicOperation.h"
#include "operator/mutation/neighborhood.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class BestImprovement : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	BestImprovement(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
					std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
					std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
					std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations);

	virtual ~BestImprovement();

	std::unique_ptr<SOL> operator()(const SOL& s);

	std::string className() const;

	void className(const std::string& class_name);

  protected:
	SOL solution_star;
	std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, SOL>> _atomicOperations;
	std::string _class_name;
};

} // namespace stocos
#endif