///
/// @file selection_minimization.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef SELECTION_DIFFERENCE_H
#define SELECTION_DIFFERENCE_H

#include <cmath>

#include "../solution/population.h"

namespace stocos {

template<class SOL>
class Selection_difference : public SolutionSelection<SOL> {
  public:
	Selection_difference(const double fitnessObjectif);

	virtual ~Selection_difference();
	bool operator()(const SOL& s1, const SOL& s2, const unsigned int numObjectif = 0) const;

	unsigned int operator()(const Population<SOL>& p) const;
  private:
	const double _fitnessObjectif;
};

} // namespace stocos
#endif