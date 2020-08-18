///
/// @file criteriaFitnessObjectif.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include <stoppingCriteria/criteriaFitnessObjectif.h>
namespace stocos {

template<typename SOL, typename TYPE_FITNESS>
CriteriaFitnessObjectif<SOL, TYPE_FITNESS>::CriteriaFitnessObjectif(TYPE_FITNESS fitness_objectif)
	: Criteria<SOL, TYPE_FITNESS>() {
	_number_of_objective = 1;
	_fitness_objectif = new TYPE_FITNESS[_number_of_objective];
	_fitness_objectif[0] = fitness_objectif;
}

template<typename SOL, typename TYPE_FITNESS>
CriteriaFitnessObjectif<SOL, TYPE_FITNESS>::CriteriaFitnessObjectif(
	TYPE_FITNESS* fitness_objectif, unsigned int number_of_objective)
	: Criteria<SOL, TYPE_FITNESS>() {
	_number_of_objective = number_of_objective;
	_fitness_objectif = new TYPE_FITNESS[_number_of_objective];
	for(unsigned int i = 0; i < number_of_objective; i++) {
		_fitness_objectif[i] = fitness_objectif[i];
	}
}

template<typename SOL, typename TYPE_FITNESS>
CriteriaFitnessObjectif<SOL, TYPE_FITNESS>::~CriteriaFitnessObjectif() {
	delete[] _fitness_objectif;
}

template<typename SOL, typename TYPE_FITNESS>
bool CriteriaFitnessObjectif<SOL, TYPE_FITNESS>::operator()(const SOL& s) {
	assert(s.numberOfObjective() == _number_of_objective);

	if(s.fitnessIsValid()) {
		for(unsigned int i = 0; i < _number_of_objective; i++) {
			if((_fitness_objectif[i] - s.getFitness(i)) != 0) { return true; }
		}
		return false;
	} else {
		return true;
	}
}

template<typename SOL, typename TYPE_FITNESS>
void CriteriaFitnessObjectif<SOL, TYPE_FITNESS>::reset() {
}

template class CriteriaFitnessObjectif<Solution<int>, unsigned int>;
template class CriteriaFitnessObjectif<SolutionArray<double, double>, double>;
template class CriteriaFitnessObjectif<SolutionArray<double, bool>, double>;
template class CriteriaFitnessObjectif<SolutionArray<int, bool>, int>;
template class CriteriaFitnessObjectif<SolutionArray<unsigned int, bool>, unsigned int>;
template class CriteriaFitnessObjectif<SolutionArray<double, unsigned int>, double>;
template class CriteriaFitnessObjectif<SolutionArray<unsigned int, unsigned int>, unsigned int>;

} // namespace stocos
