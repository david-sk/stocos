///
/// @file criteriaFitnessObjectif.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef CRITERIAFITNESSOBJECTIF_H
#define CRITERIAFITNESSOBJECTIF_H

#include <cassert>

#include "../solution/solutionArray.h"
#include "criteria.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS>
class CriteriaFitnessObjectif : public Criteria<SOL, TYPE_FITNESS> {
  public:
	CriteriaFitnessObjectif(TYPE_FITNESS fitness_objectif);

	CriteriaFitnessObjectif(TYPE_FITNESS* fitness_objectif, unsigned int number_of_objective);

	virtual ~CriteriaFitnessObjectif();

	virtual bool operator()(const SOL& s);

	void reset();

  protected:
	TYPE_FITNESS* _fitness_objectif;
	unsigned int _number_of_objective;
};

} // namespace stocos
#endif