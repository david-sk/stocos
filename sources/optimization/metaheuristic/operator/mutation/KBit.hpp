///
/// @file KBit.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief exactly mute K bits distinct
///

#ifndef OPERATION_KBIT_H
#define OPERATION_KBIT_H

#include <algorithm> // std::find
#include <memory>	// std::shared_ptr std::unique_ptr
#include <random>
#include <vector> // std::vector

#include "../../../../solution/solutionArray.hpp"
#include "../atomicOperation.hpp"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class KBit : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	KBit(std::mt19937& mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
		 unsigned int k)
		: AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, problem),
		rid(std::make_unique<std::uniform_int_distribution<unsigned int>>(0, 1)), _k(k), N(1) {
	}
	
	virtual ~KBit() {
	}

	void operator()(SOL& s) {
		backup.clear();
		std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> list = listOfMutations(s);
		for(unsigned int i = 0; i < list->size(); i++) {
			s((*list)[i].first, (*list)[i].second);
			backup.push_back((*list)[i].first);
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
		assert(_k <= s.sizeArray());

		std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> list(
			std::make_unique<std::vector<std::pair<unsigned int, TYPE_CELL>>>());

		if(s.sizeArray() != N) {
			N = s.sizeArray();
			rid = std::make_unique<std::uniform_int_distribution<unsigned int>>(0, N);
		}

		while(list->size() != _k) {
			unsigned int element = rid->operator()(this->_mt_rand);
			bool findElement = false;
			for(unsigned int i = 0; i < list->size(); i++) {
				if((*list)[i].first == element) { findElement = true; }
			}

			if(!findElement) {
				if(s(element) == 1)
					list->push_back(std::pair<unsigned int, TYPE_CELL>(element, 0));
				else
					list->push_back(std::pair<unsigned int, TYPE_CELL>(element, 1));
			}
		}

		return std::move(list);
	}

	void applyOperator(SOL& s,
					   const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations) {
		backup.clear();
		for(unsigned int i = 0; i < _listOfMutations.size(); i++) {
			s(_listOfMutations[i].first, _listOfMutations[i].second);
			backup.push_back(_listOfMutations[i].first);
		}
	}

  private:
	std::unique_ptr<std::uniform_int_distribution<unsigned int>> rid;
	unsigned int _k;
	unsigned int N;
	std::vector<unsigned int> backup;
};

} // namespace stocos
#endif