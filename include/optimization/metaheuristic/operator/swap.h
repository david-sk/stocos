///
/// @file swap.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief Echange N case distinc
///

#ifndef OPERATION_SWAP_H
#define OPERATION_SWAP_H

#include <algorithm>
#include <cassert>
#include <memory> // std::shared_ptr std::unique_ptr
#include <vector>

#include "atomicOperation.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Swap : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	Swap(std::mt19937& mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
		 unsigned int number_of_swap);

	virtual void operator()(SOL& s);

	void cancelMutations(SOL& s) const;

  private:
	std::unique_ptr<std::uniform_int_distribution<unsigned int>> rid;
	std::vector<std::pair<unsigned int, TYPE_CELL>> backup;
	unsigned int _number_of_swap;
	unsigned int N;
};

} // namespace stocos

#endif