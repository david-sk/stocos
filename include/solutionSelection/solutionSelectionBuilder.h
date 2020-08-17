///
/// @file builderSolutionSelection.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @date 2019-08-28
///
///
///

#ifndef SOLUTION_SELECTIONBUILDER_H
#define SOLUTION_SELECTIONBUILDER_H

#include <memory>

#include "../problem/problem.h"
#include "maximization.h"
#include "minimization.h"
#include "selection_difference.h"
#include "solutionSelection.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class SolutionSelectionBuilder {
  public:
	static std::unique_ptr<SolutionSelection<SOL>>
		build(const Problem<SOL, TYPE_FITNESS, TYPE_CELL>& problem,
			  const Json::Value& configuration);
};

} // namespace stocos
#endif