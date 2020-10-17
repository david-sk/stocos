///
/// @file backtracking.hpp
/// @author Jxtopher
/// @version 1
/// @date 2020-10
/// @brief see: https://en.wikipedia.org/wiki/Backtracking
///

#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../../solution/domain.h"
#include "../../solution/solution.h"
#include "../optimization.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Backtraking : public Optimization<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	Backtraking(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
				std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
				std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
				Domain<TYPE_CELL> dom);

	virtual ~Backtraking();

	std::unique_ptr<SOL> operator()(const SOL& s);

	std::unique_ptr<SOL> recursive(unsigned int currentCell, unsigned int depth, SOL s);

	std::string className() const;

	void className(const std::string& class_name);

  private:
	unsigned int nbCall;
	std::string _class_name;
	Domain<TYPE_CELL> _dom;
};

} // namespace stocos

#endif