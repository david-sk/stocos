///
/// @file simulatedAnnealing.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include <optimization/metaheuristic/simulatedAnnealing.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
SimulatedAnnealing<SOL, TYPE_FITNESS, TYPE_CELL>::SimulatedAnnealing(
	std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
	std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
	std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
	std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations)
	: OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
														  std::move(stoppingCriteria), problem),
	  _atomicOperations(std::move(atomicOperations)) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation SimulatedAnnealing";
}
template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
SimulatedAnnealing<SOL, TYPE_FITNESS, TYPE_CELL>::~SimulatedAnnealing() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> SimulatedAnnealing<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(const SOL& s) {
	solution_star = s;
	// if (!solution_star.fitnessIsValid()) {
	//     this->_problem.evaluation(solution_star);
	// }

	return std::move(std::make_unique<SOL>(solution_star));
}
template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string SimulatedAnnealing<SOL, TYPE_FITNESS, TYPE_CELL>::className() const {
	if(_class_name.empty())
		return "SimulatedAnnealing";
	else
		return _class_name;
}
template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void SimulatedAnnealing<SOL, TYPE_FITNESS, TYPE_CELL>::className(const std::string& class_name) {
	_class_name = class_name;
}

template class SimulatedAnnealing<SolutionArray<double, double>, double, double>;
template class SimulatedAnnealing<SolutionArray<double, bool>, double, bool>;
template class SimulatedAnnealing<SolutionArray<int, bool>, int, bool>;
template class SimulatedAnnealing<SolutionArray<unsigned int, bool>, unsigned int, bool>;
template class SimulatedAnnealing<SolutionArray<double, unsigned int>, double, unsigned int>;
template class SimulatedAnnealing<SolutionArray<unsigned int, unsigned int>, unsigned int,
								  unsigned int>;
} // namespace stocos