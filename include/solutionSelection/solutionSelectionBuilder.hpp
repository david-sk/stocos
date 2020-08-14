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

#include "../problem/problem.hpp"
#include "maximization.hpp"
#include "minimization.hpp"
#include "selection_difference.hpp"
#include "solutionSelection.hpp"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class solutionSelectionBuilder {
  public:
	static std::unique_ptr<SolutionSelection<SOL>>
		build(const Problem<SOL, TYPE_FITNESS, TYPE_CELL>& problem,
			  const Json::Value& configuration) {
		std::unique_ptr<SolutionSelection<SOL>> _selection = nullptr;
		if(configuration.asString() == SolutionSelection<SOL>::MAXIMIZATION) {
			_selection = std::make_unique<Maximization<SOL>>();
		} else if(configuration.asString() == SolutionSelection<SOL>::MINIMIZATION) {
			_selection = std::make_unique<Minimization<SOL>>();
		} else if(configuration.asString() == "diff") {
			// _selection =
			// std::make_unique<Selection_difference<SOL>>(_problem->getFitnessObjectif());
		} else {
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
									 " The SolutionSelection does not exist.");
		}
		return std::move(_selection);
	}
};

} // namespace stocos
#endif