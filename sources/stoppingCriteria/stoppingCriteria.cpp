///
/// @file stoppingCriteria.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-03
/// @brief
///
#include <stoppingCriteria/stoppingCriteria.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS>
StoppingCriteria<SOL, TYPE_FITNESS>::~StoppingCriteria() {
    for(auto criteria : *this) delete criteria;
    this->clear();
}

template<typename SOL, typename TYPE_FITNESS>
bool StoppingCriteria<SOL, TYPE_FITNESS>::operator()(const SOL& s) {
    bool total = true;
    for(auto criteria : *this) total = total & criteria->operator()(s);
    return total;
}

///
/// @brief add a criterion to the list
///
template<typename SOL, typename TYPE_FITNESS>
void StoppingCriteria<SOL, TYPE_FITNESS>::addCriteria(Criteria<SOL, TYPE_FITNESS>* criteria) {
    this->push_back(criteria);
}

template<typename SOL, typename TYPE_FITNESS>
void StoppingCriteria<SOL, TYPE_FITNESS>::reset() {
    for(auto criteria : *this) this->reset();
}

template class StoppingCriteria<Fitness<int>, unsigned int>;
template class StoppingCriteria<Solution<double, double>, double>;
template class StoppingCriteria<Solution<double, bool>, double>;
template class StoppingCriteria<Solution<int, bool>, int>;
template class StoppingCriteria<Solution<unsigned int, bool>, unsigned int>;
template class StoppingCriteria<Solution<double, unsigned int>, double>;
template class StoppingCriteria<Solution<unsigned int, unsigned int>, unsigned int>;

} // namespace stocos