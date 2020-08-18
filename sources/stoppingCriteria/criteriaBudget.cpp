///
/// @file criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include <stoppingCriteria/criteriaBudget.h>
namespace stocos {

template<typename SOL, typename TYPE_FITNESS>
CriteriaBudget<SOL, TYPE_FITNESS>::CriteriaBudget(unsigned int _budget)
	: Criteria<SOL, TYPE_FITNESS>(), budget(_budget) {
	consumedBudget = 0;
}

template<typename SOL, typename TYPE_FITNESS>
CriteriaBudget<SOL, TYPE_FITNESS>::~CriteriaBudget() {
}

template<typename SOL, typename TYPE_FITNESS>
bool CriteriaBudget<SOL, TYPE_FITNESS>::operator()(const SOL& s) {
	return consumedBudget++ < budget;
}

template<typename SOL, typename TYPE_FITNESS>
unsigned int CriteriaBudget<SOL, TYPE_FITNESS>::getConsumedBudget() const {
	return consumedBudget;
}

template<typename SOL, typename TYPE_FITNESS>
void CriteriaBudget<SOL, TYPE_FITNESS>::resetConsumedBudget() {
	consumedBudget = 0;
}

template<typename SOL, typename TYPE_FITNESS>
void CriteriaBudget<SOL, TYPE_FITNESS>::reset() {
	consumedBudget = 0;
}

template class CriteriaBudget<Solution<int>, unsigned int>;
template class CriteriaBudget<SolutionArray<double, double>, double>;
template class CriteriaBudget<SolutionArray<double, bool>, double>;
template class CriteriaBudget<SolutionArray<int, bool>, int>;
template class CriteriaBudget<SolutionArray<unsigned int, bool>, unsigned int>;
template class CriteriaBudget<SolutionArray<double, unsigned int>, double>;
template class CriteriaBudget<SolutionArray<unsigned int, unsigned int>, unsigned int>;

} // namespace stocos