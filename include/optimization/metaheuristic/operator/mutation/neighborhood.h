///
/// @file neighborhood.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include <list>
#include <memory> // std::shared_ptr std::unique_ptr
#include <random>
#include <utility>
#include <vector>

#include "../../../../solution/solutionArray.h"
#include "../atomicOperation.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Neighborhood : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	Neighborhood(std::mt19937& mt_rand,
				 std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem);

	virtual ~Neighborhood();

	virtual void operator()(SOL& s);

	virtual std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>>
		listOfMutations(const SOL& s);

	virtual void
		applyOperator(SOL& s,
					  const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations);
};

} // namespace stocos

#endif