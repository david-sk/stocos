///
/// @file onePlusLambda.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include <optimization/metaheuristic/onePlusLambda.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>::OnePlusLambda(
	std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
	std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
	std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
	std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations,
	unsigned int lambda)
	: OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
														  std::move(stoppingCriteria), problem),
	  _atomicOperations(std::move(atomicOperations)), _lambda(lambda) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation OnePlusLambda";
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>::~OnePlusLambda() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(const SOL& s) {
	solution_star = s;
	if(!solution_star.fitnessIsValid()) { this->_problem->evaluation(solution_star); }

	while(this->_stoppingCriteria->operator()(solution_star)) {
		this->_statistic->operator()(solution_star, className());

		solution_beta = solution_star;
		for(unsigned int i = 0; i < _lambda; i++) {
			solution_alpha = solution_star;

			_atomicOperations->operator()(solution_alpha);
			this->_problem->evaluation(solution_alpha);
			if(this->_problem->solutionSelection(solution_alpha, solution_beta)) {
				solution_beta = solution_alpha;
			}
		}
		solution_star = solution_beta;
	}

	return std::move(std::make_unique<SOL>(solution_star));
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>::className() const {
	if(_class_name.empty())
		return "OnePlusLambda";
	else
		return _class_name;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>::className(const std::string& class_name) {
	_class_name = class_name;
}

template class OnePlusLambda<SolutionArray<double, double>, double, double>;
template class OnePlusLambda<SolutionArray<double, bool>, double, bool>;
template class OnePlusLambda<SolutionArray<int, bool>, int, bool>;
template class OnePlusLambda<SolutionArray<unsigned int, bool>, unsigned int, bool>;
template class OnePlusLambda<SolutionArray<double, unsigned int>, double, unsigned int>;
template class OnePlusLambda<SolutionArray<unsigned int, unsigned int>, unsigned int, unsigned int>;
} // namespace stocos