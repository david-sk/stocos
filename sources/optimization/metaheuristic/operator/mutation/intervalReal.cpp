///
/// @file flipBit.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief intervalle real [a,b]
///
#include <optimization/metaheuristic/operator/mutation/intervalReal.h>
namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
IntervalReal<SOL, TYPE_FITNESS, TYPE_CELL>::IntervalReal(
	std::mt19937& mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
	unsigned int c, double a, double b)
	: AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, problem), _c(c), _a(a), _b(b) {
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
	//! use domain.hpp
	// if (s.sizeArray() != N) {
	//     N = s.sizeArray();
	//     mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
	//     backup.reserve(N);
	// }

	// for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
	//     if (urd_0_1->operator()(this->_mt_rand) < mutation_rate) {

	//         try {
	//             TYPE_CELL new_value_of_the_cell = s(i) + urd->operator()(this->_mt_rand);
	//             std::pair<TYPE_CELL, TYPE_CELL> dom = this->_problem->domain(i);

	//             if (new_value_of_the_cell < dom.first)
	//                 new_value_of_the_cell = dom.first;
	//             else if (dom.second < new_value_of_the_cell)
	//                  new_value_of_the_cell = dom.second;

	//             s(i, new_value_of_the_cell);
	//         }  catch (...) {
	//             s(i, s(i) + urd->operator()(this->_mt_rand));
	//         }
	//     }
	// }
}

template class IntervalReal<SolutionArray<double, double>, double, double>;
template class IntervalReal<SolutionArray<double, bool>, double, bool>;
template class IntervalReal<SolutionArray<int, bool>, int, bool>;
template class IntervalReal<SolutionArray<unsigned int, bool>, unsigned int, bool>;
template class IntervalReal<SolutionArray<double, unsigned int>, double, unsigned int>;
template class IntervalReal<SolutionArray<unsigned int, unsigned int>, unsigned int, unsigned int>;
} // namespace stocos