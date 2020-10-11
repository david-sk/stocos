///
/// @file flipBit.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief interval integer [a,b]
///
#include <optimization/metaheuristic/operator/mutation/intervalInteger.h>
namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
IntervalInteger<SOL, TYPE_FITNESS, TYPE_CELL>::IntervalInteger(std::mt19937& mt_rand,
															   unsigned int c, double a, double b)
	: AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand), _c(c), _a(a), _b(b) {
	urd_0_1 = std::make_unique<std::uniform_real_distribution<>>(0, 1);
	rid =
		std::make_unique<std::uniform_int_distribution<int>>(_a, _b); // unsigned int -> TYPE_CELL ?
	mutation_rate = 0.5;
	N = 0;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void IntervalInteger<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(SOL& s) {
	if(s.sizeArray() != N) {
		N = s.sizeArray();
		mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
	}

	for(unsigned int i = 0; i < s.sizeArray(); i++) {
		if(urd_0_1->operator()(this->_mt_rand) < mutation_rate) {
			s(i, static_cast<TYPE_CELL>(rid->operator()(this->_mt_rand)));
		}
	}
}

template class IntervalInteger<SolutionArray<double, double>, double, double>;
template class IntervalInteger<SolutionArray<double, bool>, double, bool>;
template class IntervalInteger<SolutionArray<int, bool>, int, bool>;
template class IntervalInteger<SolutionArray<unsigned int, bool>, unsigned int, bool>;
template class IntervalInteger<SolutionArray<double, unsigned int>, double, unsigned int>;
template class IntervalInteger<SolutionArray<unsigned int, unsigned int>, unsigned int,
							   unsigned int>;
template class IntervalInteger<SolutionArray<int, int>, int, int>;
} // namespace stocos