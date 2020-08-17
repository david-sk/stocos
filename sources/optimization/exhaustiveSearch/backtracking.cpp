///
/// @file backtracking.hpp
/// @author Jxtopher
/// @version 1
/// @date 2019
/// @brief *
///

#include <optimization/exhaustiveSearch/backtracking.h>


namespace stocos {


template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::Backtraking(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
			std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
			std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
			const unsigned int nbDigit, const unsigned int len_string)
	: OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
															std::move(stoppingCriteria), problem),
		_nbDigit(nbDigit), _len_string(len_string) {
	nbCall = 0;
	_string = std::unique_ptr<unsigned int[]>(new unsigned int[_len_string]);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::~Backtraking() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(const SOL& s) {
	//
	std::unique_ptr<SOL> result;
	return std::move(result);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::recursive(unsigned int currentCell) {
	// current_sol.print();
	if(_len_string == currentCell) {
		// for(unsigned int j = 0 ; j < _len_string ; j++)
		//     cout<<string[j];
		// std::cout<<std::endl;
		// cout<<"Wine : ";
		// current_sol.print();
	} else {
		unsigned int i = 0;
		while(i < _nbDigit) {
			_string[currentCell] = i;

			// Verification des contraites
			// if (filtering(current_sol, currentCell + 1)) {
			// if(this-> _problem.filtering(string)) {
			// Descendre dans l'arbre (parcourt en profondeur)
			recursive(currentCell + 1);
			//}
			i++;
		}
	}
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::className() const {
	if(_class_name.empty())
		return "Backtraking";
	else
		return _class_name;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void Backtraking<SOL, TYPE_FITNESS, TYPE_CELL>::className(const std::string& class_name) {
	_class_name = class_name;
}

} // namespace stocos