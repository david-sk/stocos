///
/// @file tabuSearch.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief F. Glover, "Future paths for integer programming and links to artificial intelligence,"
/// Computers & Operations Research, vol. 13, pp. 533-549, 1986.
///
#include <optimization/metaheuristic/tabuSearch.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
TabuSearch<SOL,TYPE_FITNESS,TYPE_CELL>::TabuSearch(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
			std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
			std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
			std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations,
			unsigned int sizeOfTabuList)
	: OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
															std::move(stoppingCriteria), problem),
		_atomicOperations(std::move(atomicOperations)) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation TabuSearch";
	tabuList.set_capacity(sizeOfTabuList);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
TabuSearch<SOL,TYPE_FITNESS,TYPE_CELL>::~TabuSearch() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> TabuSearch<SOL,TYPE_FITNESS,TYPE_CELL>::operator()(const SOL& s) {
	solution_star = s;
	if(!solution_star.fitnessIsValid()) { this->_problem->evaluation(solution_star); }

	while(this->_stoppingCriteria->operator()(solution_star)) {
		this->_statistic->operator()(solution_star, className());

		solution_beta = solution_star;
		_atomicOperations->operator()(solution_beta);

		// Recherche dans la liste tabou
		bool inTheTabooList = false;
		for(SOL solutionTabu : tabuList) {
			if(solutionTabu == solution_beta) {
				inTheTabooList = true;
				break;
			}
		}

		if(!inTheTabooList) {
			this->_problem->evaluation(solution_beta);
			if(this->_problem->solutionSelection(solution_beta, solution_star)) {
				solution_star = solution_beta;
			}
		}
		tabuList.push_back(solution_beta);
	}

	return std::move(std::make_unique<SOL>(solution_star));
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string TabuSearch<SOL,TYPE_FITNESS,TYPE_CELL>::className() const {
	if(_class_name.empty())
		return "TabuSearch";
	else
		return _class_name;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void TabuSearch<SOL,TYPE_FITNESS,TYPE_CELL>::className(const std::string& class_name) {
	_class_name = class_name;
}

} // namespace stocos