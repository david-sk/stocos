///
/// @file solver.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef SOLVER_H
#define SOLVER_H

#include <random>
#include <string>

#include "../problem/problem.hpp"

namespace stocos {

class Solver {
  public:
	Solver() {
	}
	virtual ~Solver() {
	}

	virtual void operator()() = 0;

  protected:
};

} // namespace stocos

#endif
