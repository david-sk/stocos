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

#include "../../../../solution/solutionArray.h"
#include "../atomicOperation.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class KBit : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	KBit(std::mt19937& mt_rand, unsigned int k);

	virtual ~KBit();

	void operator()(SOL& s);

	void cancelMutations(SOL& s) const;
	std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL& s);

	void applyOperator(SOL& s,
					   const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations);

  private:
	std::unique_ptr<std::uniform_int_distribution<unsigned int>> rid;
	unsigned int _k;
	unsigned int N;
	std::vector<unsigned int> backup;
};

} // namespace stocos
#endif