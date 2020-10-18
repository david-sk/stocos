///
/// @file iteratedLocalSearch.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief Iterated local search Ramalhinho-Lourenço, Helena, Martin, Olivier C. and Stützle,
/// Thomas, (2000)
///        Iterated local search, Economics Working Papers, Department of Economics and Business,
///        Universitat Pompeu Fabra, https://EconPapers.repec.org/RePEc:upf:upfgen:513.
///        (https://econ-papers.upf.edu/papers/513.pdf)
///

#include <optimization/metaheuristic/iteratedLocalSearch.h>

namespace stocos {

// Exploration-Exploitation
template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>::IteratedLocalSearch(
	std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
	std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
	std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
	std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> exploration,
	std::unique_ptr<Optimization<SOL, TYPE_FITNESS, TYPE_CELL>> exploitation)
	: Optimization<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
												 std::move(stoppingCriteria), problem),
	  _exploration(std::move(exploration)), _exploitation(std::move(exploitation)) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation IteratedLocalSearch";
	_exploitation->className("ILS>" + _exploitation->className());
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>::~IteratedLocalSearch() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(const SOL& s) {
	solution_star = s;
	if(!solution_star.fitnessIsValid()) { this->_problem->evaluation(solution_star); }

	while(this->_stoppingCriteria->operator()(solution_star)) {
		this->_statistic->operator()(solution_star, className());

		solution_beta = solution_star;

		_exploration->operator()(solution_beta);
		std::unique_ptr<SOL> solution_beta_beta = _exploitation->operator()(solution_beta);

		this->_problem->evaluation(*solution_beta_beta);
		if(this->_problem->solutionSelection(*solution_beta_beta, solution_star)) {
			solution_star = *solution_beta_beta;
		}
	}

	return std::move(std::make_unique<SOL>(solution_star));
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>::className() const {
	if(_class_name.empty())
		return "IteratedLocalSearch";
	else
		return _class_name;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>::className(const std::string& class_name) {
	_class_name = class_name;
}

template class IteratedLocalSearch<Solution<double, double>, double, double>;
template class IteratedLocalSearch<Solution<double, bool>, double, bool>;
template class IteratedLocalSearch<Solution<int, bool>, int, bool>;
template class IteratedLocalSearch<Solution<unsigned int, bool>, unsigned int, bool>;
template class IteratedLocalSearch<Solution<double, unsigned int>, double, unsigned int>;
template class IteratedLocalSearch<Solution<unsigned int, unsigned int>, unsigned int,
								   unsigned int>;
} // namespace stocos