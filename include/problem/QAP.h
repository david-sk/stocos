///
/// @file QAP.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-10
/// @brief Quadratic Assignment Problem
///
///             ---  ---
///             |    |
///      sol =  /    /    a    b         .
///             ---  ---   ij   p(i),p(j)
///              i    j
///         see : https://www.opt.math.tugraz.at/qaplib/inst.html
///         see : http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.94.9558&rep=rep1&type=pdf
///

#ifndef EVALQAP_H
#define EVALQAP_H

#include <iostream>
#include <memory>

#include "../solution/solution.h"
#include "problem.h"

namespace stocos {

using TYPE_FITNESS_QAP = unsigned int;
using TYPE_CELL_QAP = unsigned int;
using SOL_QAP = Solution<TYPE_FITNESS_QAP, TYPE_CELL_QAP>;
class QAP : public Problem<SOL_QAP, TYPE_FITNESS_QAP, TYPE_CELL_QAP> {
  public:
	QAP(const std::string& fileInstance);

	QAP(unsigned int _n, unsigned int** _A, unsigned int** _B);

	// virtual ~QAP();
	void loadJson(const Json::Value& config);

	void evaluation(SOL_QAP& p);

	void resetSolution(SOL_QAP& s) const;
	void showA() const;

  private:
	unsigned int n;   // instance size
	unsigned int** A; // distance between locations i and j
	unsigned int** B; // the flow between facilities r and s
};

} // namespace stocos
#endif
