///
/// @file flipBit.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief intervalle real [a,b]
///

#ifndef OPERATION_INTERVALREAL_H
#define OPERATION_INTERVALREAL_H

#include <memory> // std::shared_ptr std::unique_ptr
#include <random>
#include <vector>

#include "../../../../solution/solutionArray.hpp"

#include "../atomicOperation.hpp"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class IntervalReal : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	IntervalReal(std::mt19937& mt_rand,
				 std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem, unsigned int c,
				 double a, double b)
		: AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, problem), _c(c), _a(a), _b(b) {
		urd_0_1 = std::make_unique<std::uniform_real_distribution<>>(0, 1);
		urd = std::make_unique<std::uniform_real_distribution<>>(a, b);
		mutation_rate = 0.5;
		N = 0;
	}
	virtual ~IntervalReal() {}

	void operator()(SOL& s) {
		if (s.sizeArray() != N) {
		    N = s.sizeArray();
		    mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
		    backup.reserve(N);
		}

		for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
		    if (urd_0_1->operator()(this->_mt_rand) < mutation_rate) {
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

  private:
	const unsigned int _c; // < Nombre de case à mute / arraySize
	const unsigned int _a; // < Lower bound
	const unsigned int _b; // < Upper bollard
	std::unique_ptr<std::uniform_real_distribution<>> urd_0_1;
	std::unique_ptr<std::uniform_real_distribution<>> urd;
	double mutation_rate;
	unsigned int N;
	std::vector<unsigned int> backup;
};

} // namespace stocos
#endif