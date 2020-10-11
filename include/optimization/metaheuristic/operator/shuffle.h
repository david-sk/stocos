///
/// @file shuffle.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief
///

#ifndef OPERATION_SHUFFLE_H
#define OPERATION_SHUFFLE_H

#include <algorithm> // std::random_shuffle
#include <memory>	// std::shared_ptr std::unique_ptr

#include "atomicOperation.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Shuffle : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	Shuffle(std::mt19937& mt_rand);

	~Shuffle();

	virtual void operator()(SOL& s);

  private:
	std::vector<TYPE_CELL> index;
};

} // namespace stocos
#endif