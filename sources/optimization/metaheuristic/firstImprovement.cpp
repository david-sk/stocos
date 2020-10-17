///
/// @file firstImprovement.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include <optimization/metaheuristic/firstImprovement.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::FirstImprovement(
	std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
	std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
	std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
	std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations)
	: Optimization<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
														  std::move(stoppingCriteria), problem),
	  _atomicOperations(std::move(atomicOperations)) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation FirstImprovement";
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::~FirstImprovement() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(const SOL& s) {
	solution_star = s;
	if(!solution_star.fitnessIsValid()) { this->_problem->evaluation(solution_star); }

	while(this->_stoppingCriteria->operator()(solution_star)) {
		this->_statistic->operator()(solution_star, className());

		solution_beta = solution_star;

		_atomicOperations->operator()(solution_beta);
		this->_problem->evaluation(solution_beta);
		if(this->_problem->solutionSelection(solution_beta, solution_star)) {
			solution_star = solution_beta;
		}
	}
	return std::move(std::make_unique<SOL>(solution_star));
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::className() const {
	if(_class_name.empty())
		return "FirstImprovement";
	else
		return _class_name;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::className(const std::string& class_name) {
	_class_name = class_name;
}

template class FirstImprovement<Solution<double, double>, double, double>;
template class FirstImprovement<Solution<double, bool>, double, bool>;
template class FirstImprovement<Solution<int, bool>, int, bool>;
template class FirstImprovement<Solution<unsigned int, bool>, unsigned int, bool>;
template class FirstImprovement<Solution<double, unsigned int>, double, unsigned int>;
template class FirstImprovement<Solution<unsigned int, unsigned int>, unsigned int, unsigned int>;
} // namespace stocos