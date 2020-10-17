///
/// @file optimization.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <memory>
#include <random>
#include <string>

#include "../problem/problem.h"
#include "../statistic/statistic.h"
#include "../stoppingCriteria/stoppingCriteria.h"

namespace stocos {

template<class SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Optimization {
  public:
	Optimization(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
						  std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
						  std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem)
		: _mt_rand(mt_rand), _statistic(std::move(statistic)),
		  _stoppingCriteria(std::move(stoppingCriteria)), _problem(problem) {
	}
	virtual ~Optimization() {
	}

	virtual void reset() {
		_stoppingCriteria->reset();
	}
	virtual std::unique_ptr<SOL> operator()(const SOL& s) = 0;
	virtual std::string className() const = 0;
	virtual void className(const std::string& class_name) = 0;

  protected:
	std::mt19937& _mt_rand;
	std::shared_ptr<Statistic<SOL>> _statistic;
	std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> _stoppingCriteria;
	std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
};

} // namespace stocos
#endif