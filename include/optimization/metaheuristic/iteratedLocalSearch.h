///
/// @file iteratedLocalSearch.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief Iterated local search Ramalhinho-Lourenço, Helena, Martin, Olivier C. and Stützle,
/// Thomas, (2000)
///        Iterated local search, Economics Working Papers, Department of Economics and Business,
///        Universitat Pompeu Fabra, https://EconPapers.repec.org/RePEc:upf:upfgen:513.
///        (https://econ-papers.upf.edu/papers/513.pdf)
///

#ifndef ITERATEDLOCALSEARCH_H
#define ITERATEDLOCALSEARCH_H

#include <memory>
#include <random>
#include <string>

#include "../../problem/problem.h"
#include "../../statistic/statistic.h"
#include "../../stoppingCriteria/stoppingCriteria.h"
#include "operator/atomicOperation.h"
#include "../optimizationAlgorithm.h"

namespace stocos {

// Exploration-Exploitation
template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class IteratedLocalSearch : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	IteratedLocalSearch(
		std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
		std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
		std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
		std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> exploration,
		std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> exploitation);

	~IteratedLocalSearch();

	std::unique_ptr<SOL> operator()(const SOL& s);
	std::string className() const;

	void className(const std::string& class_name);
  protected:
	std::string _class_name;
	std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _exploration;
	std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> _exploitation;
	SOL solution_star;
	SOL solution_beta;
};

} // namespace stocos
#endif
