///
/// @file selection_minimization.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include <solutionSelection/selection_difference.h>

namespace stocos {

template<class SOL>
Selection_difference<SOL>::Selection_difference(const double fitnessObjectif)
	: _fitnessObjectif(fitnessObjectif) {
}

template<class SOL>
Selection_difference<SOL>::~Selection_difference() {
}

template<class SOL>
bool Selection_difference<SOL>::operator()(const SOL& s1, const SOL& s2,
										   const unsigned int numObjectif) const {
	assert(s1.fitnessIsValid(numObjectif));
	assert(s2.fitnessIsValid(numObjectif));
	return abs(_fitnessObjectif - s1.getFitness(numObjectif)) <
		   abs(_fitnessObjectif - s2.getFitness(numObjectif));
}

template<class SOL>
unsigned int Selection_difference<SOL>::operator()(const Population<SOL>& p) const {
	return 0;
}

template class Selection_difference<Solution<int>>;
template class Selection_difference<SolutionArray<double, double>>;
template class Selection_difference<SolutionArray<double, bool>>;
template class Selection_difference<SolutionArray<int, bool>>;
template class Selection_difference<SolutionArray<unsigned int, bool>>;
template class Selection_difference<SolutionArray<double, unsigned int>>;
template class Selection_difference<SolutionArray<unsigned int, unsigned int>>;
} // namespace stocos