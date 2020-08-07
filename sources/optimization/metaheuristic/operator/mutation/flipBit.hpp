///
/// @file flipBit.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef OPERATION_FLIPBIT_H
#define OPERATION_FLIPBIT_H

#include <memory> // std::shared_ptr std::unique_ptr
#include <random> // std::mt19937
#include <vector> // std::vector

#include "../../../../solution/solutionArray.hpp"

#include "../atomicOperation.hpp"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class FlipBit : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	FlipBit(std::mt19937& mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
			unsigned int c)
		: AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, problem), _c(c), N(0) {
		urd = std::make_unique<std::uniform_real_distribution<>>(0, 1);
	}
	virtual ~FlipBit() {
	}

	void operator()(SOL& s) {
		backup.clear();
		if(s.sizeArray() != N) {
			N = s.sizeArray();
			mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
			backup.reserve(N);
		}

		for(unsigned int i = 0; i < s.sizeArray(); i++) {
			if(urd->operator()(this->_mt_rand) < mutation_rate) {
				if(s(i) == 1)
					s(i, 0);
				else
					s(i, 1);
				backup.push_back(i);
			}
		}
	}

	void cancelMutations(SOL& s) const {
		for(unsigned int i = 0; i < backup.size(); i++) {
			if(s(backup[i]) == 1)
				s(backup[i], 0);
			else
				s(backup[i], 1);
		}
	}

	std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL& s) {
		std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> list(
			std::make_unique<std::vector<std::pair<unsigned int, TYPE_CELL>>>());

		if(s.sizeArray() != N) {
			N = s.sizeArray();
			mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
		}

		for(unsigned int i = 0; i < s.sizeArray(); i++) {
			if(urd->operator()(this->_mt_rand) < mutation_rate) {
				if(s(i) == 1)
					list->push_back(std::pair<unsigned int, TYPE_CELL>(i, 0));
				else
					list->push_back(std::pair<unsigned int, TYPE_CELL>(i, 1));
			}
		}
		return std::move(list);
	}

	void applyOperator(SOL& s,
					   const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations) {
		backup.clear();
		for(unsigned int i = 0; i < _listOfMutations.size(); i++) {
			s(_listOfMutations[i].first, _listOfMutations[i].second);
			backup.push_back(i);
		}
	}

  private:
	const unsigned int _c; // < parameter c
	unsigned int N;
	std::unique_ptr<std::uniform_real_distribution<>> urd;
	double mutation_rate;

	std::vector<unsigned int> backup;
};

} // namespace stocos
#endif