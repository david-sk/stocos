///
/// @file selection_minimization.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef MINIMIZATION_H
#define MINIMIZATION_H

#include "../solution/solutionArray.h"
#include "solutionSelection.h"

namespace stocos {

template<class SOL>
class Minimization : public SolutionSelection<SOL> {
  public:
	Minimization();

	virtual ~Minimization();

	bool operator()(const SOL& s1, const SOL& s2, const unsigned int numObjectif = 0) const;

	unsigned int operator()(const Population<SOL>& p) const;
};

} // namespace stocos

#endif