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

namespace stocos {

template<class SOL> class Selection_difference : public SolutionSelection<SOL> {
  public:
	Selection_difference(const double fitnessObjectif) : _fitnessObjectif(fitnessObjectif) {}

	virtual ~Selection_difference() {}

	bool operator()(const SOL& s1, const SOL& s2, const unsigned int numObjectif = 0) const {
		assert(s1.fitnessIsValid(numObjectif));
		assert(s2.fitnessIsValid(numObjectif));
		return abs(_fitnessObjectif - s1.getFitness(numObjectif)) <
			   abs(_fitnessObjectif - s2.getFitness(numObjectif));
	}

	unsigned int operator()(const Population<SOL>& p) const { return 0; }

  private:
	const double _fitnessObjectif;
};

} // namespace stocos
#endif