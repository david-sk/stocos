///
/// @file filters.cpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2021-10
/// @brief
///

#include <filtering/filters.h>
#include <solution/solution.h>

namespace stocos {

template<typename SOL>
bool Filters<SOL>::operator()(const SOL& s) const {
	bool ret = true;
	for(auto it = this->begin(); it != this->end(); ++it) ret = ret && (*it)(s);
	return ret;
}

template class Filters<Fitness<int>>;
template class Filters<Fitness<double>>;
template class Filters<Solution<double, double>>;
template class Filters<Solution<double, bool>>;
template class Filters<Solution<int, bool>>;
template class Filters<Solution<unsigned int, bool>>;
template class Filters<Solution<double, unsigned int>>;
template class Filters<Solution<unsigned int, unsigned int>>;

} // namespace stocos