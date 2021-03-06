///
/// @file shuffle.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief
///

#include <optimization/metaheuristic/operator/shuffle.h>
namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Shuffle<SOL, TYPE_FITNESS, TYPE_CELL>::Shuffle(std::mt19937& mt_rand)
    : AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand) {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Shuffle<SOL, TYPE_FITNESS, TYPE_CELL>::~Shuffle() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void Shuffle<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(SOL& s) {
    if(index.size() != s.sizeArray()) {
        index.clear();
        for(unsigned int i = 0; i < s.sizeArray(); i++) index.push_back(i);
    }

    std::shuffle(index.begin(), index.end(), this->_mt_rand);
    for(unsigned int i = 0; i < s.sizeArray(); i++) {
        TYPE_CELL tmp = s(i);
        s(i, s(index[i]));
        s(index[i], tmp);
    }
}

template class Shuffle<Solution<double, double>, double, double>;
template class Shuffle<Solution<double, bool>, double, bool>;
template class Shuffle<Solution<int, bool>, int, bool>;
template class Shuffle<Solution<unsigned int, bool>, unsigned int, bool>;
template class Shuffle<Solution<double, unsigned int>, double, unsigned int>;
template class Shuffle<Solution<unsigned int, unsigned int>, unsigned int, unsigned int>;
template class Shuffle<Solution<int, int>, int, int>;
} // namespace stocos