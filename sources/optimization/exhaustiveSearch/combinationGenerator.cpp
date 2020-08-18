///
/// @file combinationGenerator.hpp
/// @author J_xtopher
/// @version 1
/// @date 2019
/// @brief https://fr.wikipedia.org/wiki/Recherche_e_xhaustive
///
#include <optimization/exhaustiveSearch/combinationGenerator.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
CombinationGenerator<SOL, TYPE_FITNESS, TYPE_CELL>::CombinationGenerator(
	std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
	std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
	std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem)
	: OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
														  std::move(stoppingCriteria), problem) {
	_nb_call = 0;
	_nb_digit = 0;
	_len_string = 0;
	_x = false;
	_cpt = false;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
CombinationGenerator<SOL, TYPE_FITNESS, TYPE_CELL>::~CombinationGenerator() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void CombinationGenerator<SOL, TYPE_FITNESS, TYPE_CELL>::reset() {
	for(unsigned int j = 0; j < _len_string; j++) _string[j] = 0;

	_x = false;
	_cpt = 0;

	while(_string[_cpt] == (_nb_digit - 1)) {
		_cpt++;
		_x = true;
	}
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void CombinationGenerator<SOL, TYPE_FITNESS, TYPE_CELL>::step() {
	_string[_cpt]++;

	if(_x) {
		for(unsigned int j = 0; j < _cpt; j++) _string[j] = 0;
		_cpt = 0;
	}

	while(_string[_cpt] == (_nb_digit - 1)) {
		_cpt++;
		_x = true;
	}
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
bool CombinationGenerator<SOL, TYPE_FITNESS, TYPE_CELL>::stop() {
	return _cpt < (_len_string);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> CombinationGenerator<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(const SOL& s) {
	// if(s.domain == nullptr)
	// 	throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
	// 							 " [-] domain == nullptr)");
	// // initialization
	// _nb_digit = s.domain->size_domain(0);
	throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
							 " [-] domain == nullptr)");
	_len_string = s.sizeArray();
	_string = std::unique_ptr<unsigned int[]>(new unsigned int[_len_string]);

	solution = std::make_unique<SOL>(s);
	reset();

	// Convert
	for(unsigned int i = 0; i < _len_string; i++) { solution->operator()(i, _string[i]); }

	// applay filtering
	this->_problem->evaluation(*solution);
	solution_star = std::make_unique<SOL>(*solution);
	if(this->_problem->solutionSelection(*solution, *solution_star)) {
		solution_star.reset(new SOL(*solution));
		std::cout << *solution_star << std::endl;
	}

	do {
		step();

		// Convert
		for(unsigned int i = 0; i < _len_string; i++) { solution->operator()(i, _string[i]); }

		// apply filtering
		this->_problem->evaluation(*solution);
		if(this->_problem->solutionSelection(*solution, *solution_star)) {
			solution_star.reset(new SOL(*solution));
			std::cout << *solution_star << std::endl;
		}
	} while(stop());

	return std::move(solution_star);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string CombinationGenerator<SOL, TYPE_FITNESS, TYPE_CELL>::className() const {
	if(_class_name.empty())
		return "CombinationGenerator";
	else
		return _class_name;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void CombinationGenerator<SOL, TYPE_FITNESS, TYPE_CELL>::className(const std::string& class_name) {
	_class_name = class_name;
}

template class CombinationGenerator<SolutionArray<double, double>, double, double>;
template class CombinationGenerator<SolutionArray<double, bool>, double, bool>;
template class CombinationGenerator<SolutionArray<int, bool>, int, bool>;
template class CombinationGenerator<SolutionArray<unsigned int, bool>, unsigned int, bool>;
template class CombinationGenerator<SolutionArray<double, unsigned int>, double, unsigned int>;
template class CombinationGenerator<SolutionArray<unsigned int, unsigned int>, unsigned int,
									unsigned int>;
} // namespace stocos