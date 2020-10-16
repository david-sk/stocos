///
/// @file selection.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef SOLUTION_SELECTION_H
#define SOLUTION_SELECTION_H

#include "../solution/population.h"
#include "../solution/solution.h"

namespace stocos {

template<class SOL>
class SolutionSelection {
  public:
	static constexpr const char* MAXIMIZATION = "max";
	static constexpr const char* MINIMIZATION = "min";

	SolutionSelection() {
	}

	virtual ~SolutionSelection() {
	}

	virtual bool operator()(const SOL& s1, const SOL& s2,
							const unsigned int numObjectif = 0) const = 0;
	virtual unsigned int operator()(const Population<SOL>& p) const = 0;
};

} // namespace stocos

#endif