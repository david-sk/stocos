///
/// @file optimizationAlgorithm.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef OPTIMIZATIONALGORITHM_H
#define OPTIMIZATIONALGORITHM_H

#include <memory>
#include <random>
#include <string>

#include "../problem/problem.hpp"
#include "../statistic/statistic.hpp"
#include "../stoppingCriteria/stoppingCriterias.hpp"

namespace stocos {

template<class SOL, typename TYPE_FITNESS, typename TYPE_CELL> class OptimizationAlgorithm {
  public:
	OptimizationAlgorithm(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
						  std::unique_ptr<StoppingCriterias<SOL, TYPE_FITNESS>> stoppingCriterias,
						  std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem)
		: _mt_rand(mt_rand), _statistic(std::move(statistic)),
		  _stoppingCriterias(std::move(stoppingCriterias)), _problem(problem) {}
	virtual ~OptimizationAlgorithm() {}

	virtual void reset() { _stoppingCriterias->reset(); }
	virtual std::unique_ptr<SOL> operator()(const SOL& s) = 0;
	virtual std::string className() const = 0;
	virtual void className(const std::string& class_name) = 0;

  protected:
	std::mt19937& _mt_rand;
	std::shared_ptr<Statistic<SOL>> _statistic;
	std::unique_ptr<StoppingCriterias<SOL, TYPE_FITNESS>> _stoppingCriterias;
	std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
};

} // namespace stocos
#endif