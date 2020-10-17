///
/// @file combinationGenerator.hpp
/// @author J_xtopher
/// @version 1
/// @date 2019
/// @brief https://fr.wikipedia.org/wiki/Recherche_e_xhaustive
///

#ifndef COMBINATIONGENERATOR_H
#define COMBINATIONGENERATOR_H

#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "../../problem/problem.h"
#include "../../solution/population.h"
#include "../../solution/solution.h"
#include "../optimization.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class CombinationGenerator : public Optimization<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	CombinationGenerator(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
						 std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
						 std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem);

	virtual ~CombinationGenerator();

	void reset();

	void step();

	bool stop();
	std::unique_ptr<SOL> operator()(const SOL& s);

	std::string className() const;

	void className(const std::string& class_name);

  private:
	unsigned int _nb_digit;
	unsigned int _len_string;
	std::string _class_name;

	unsigned int _nb_call;
	std::unique_ptr<unsigned int[]> _string;
	std::unique_ptr<SOL> solution;
	std::unique_ptr<SOL> solution_star;

	bool _x;
	unsigned int _cpt;
};

} // namespace stocos
#endif