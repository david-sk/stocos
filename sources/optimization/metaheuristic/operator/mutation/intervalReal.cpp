///
/// @file flipBit.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief interval real [a,b]
///
#include <optimization/metaheuristic/operator/mutation/intervalReal.h>
namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
IntervalReal<SOL, TYPE_FITNESS, TYPE_CELL>::IntervalReal(std::mt19937& mt_rand, unsigned int c,
														 double a, double b)
	: AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand), _c(c), _a(a), _b(b) {
	urd_0_1 = std::make_unique<std::uniform_real_distribution<>>(0, 1);
	urd = std::make_unique<std::uniform_real_distribution<>>(a, b);
	mutation_rate = 0.5;
	N = 0;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
IntervalReal<SOL, TYPE_FITNESS, TYPE_CELL>::~IntervalReal() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void IntervalReal<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(SOL& s) {
	if(s.sizeArray() != N) {
		N = s.sizeArray();
		mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
		backup.reserve(N);
	}

	for(unsigned int i = 0; i < s.sizeArray(); i++) {
		if(urd_0_1->operator()(this->_mt_rand) < mutation_rate) {
			s(i, s(i) + urd->operator()(this->_mt_rand));
		}
	}
}

template class IntervalReal<Solution<double, double>, double, double>;
template class IntervalReal<Solution<double, bool>, double, bool>;
template class IntervalReal<Solution<int, bool>, int, bool>;
template class IntervalReal<Solution<unsigned int, bool>, unsigned int, bool>;
template class IntervalReal<Solution<double, unsigned int>, double, unsigned int>;
template class IntervalReal<Solution<unsigned int, unsigned int>, unsigned int, unsigned int>;
template class IntervalReal<Solution<int, int>, int, int>;
} // namespace stocos