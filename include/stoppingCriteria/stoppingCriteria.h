///
/// @file stoppingCriteria.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-03
/// @brief
///

#ifndef STOPPINGCRITERIA_H
#define STOPPINGCRITERIA_H

#include <list>

#include "../solution/solutionArray.h"
#include "criteria.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS>
class StoppingCriteria : private std::list<Criteria<SOL, TYPE_FITNESS>*> {
  public:
	virtual ~StoppingCriteria();

	bool operator()(const SOL& s);
	///
	/// @brief add a criterion to the list
	///
	void addCriteria(Criteria<SOL, TYPE_FITNESS>* criteria);

	void reset();
};

} // namespace stocos
#endif