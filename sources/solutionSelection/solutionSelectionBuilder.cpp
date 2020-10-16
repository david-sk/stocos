///
/// @file builderSolutionSelection.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @date 2019-08-28
///
///
///
#include <solutionSelection/solutionSelectionBuilder.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SolutionSelection<SOL>>
	SolutionSelectionBuilder<SOL, TYPE_FITNESS, TYPE_CELL>::build(
		const Problem<SOL, TYPE_FITNESS, TYPE_CELL>& problem, const Json::Value& configuration) {
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

template class SolutionSelectionBuilder<Solution<double, double>, double, double>;
template class SolutionSelectionBuilder<Solution<double, bool>, double, bool>;
template class SolutionSelectionBuilder<Solution<int, bool>, int, bool>;
template class SolutionSelectionBuilder<Solution<unsigned int, bool>, unsigned int, bool>;
template class SolutionSelectionBuilder<Solution<double, unsigned int>, double, unsigned int>;
template class SolutionSelectionBuilder<Solution<unsigned int, unsigned int>, unsigned int,
										unsigned int>;

} // namespace stocos