///
/// @file stoppingCriteria.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2021-10
/// @brief
///

#include <filtering/filters.h>

namespace stocos {

template<typename SOL>
bool Filters<SOL>::operator()(const SOL& s) const {
	bool ret = true;
	for(auto it = this->begin(); it != this->end(); ++it) ret = ret && (*it)(s);
	return ret;
}

template class Filters<Solution<int>>;
template class Filters<Solution<double>>;
template class Filters<SolutionArray<double, double>>;
template class Filters<SolutionArray<double, bool>>;
template class Filters<SolutionArray<int, bool>>;
template class Filters<SolutionArray<unsigned int, bool>>;
template class Filters<SolutionArray<double, unsigned int>>;
template class Filters<SolutionArray<unsigned int, unsigned int>>;

} // namespace stocos