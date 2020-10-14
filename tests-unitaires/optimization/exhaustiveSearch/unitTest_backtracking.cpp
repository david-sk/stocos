///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../../unitTest.h"

#ifndef UNITTEST_BACKTRACKING_H
#define UNITTEST_BACKTRACKING_H

#include <memory>
#include <typeinfo>

#include <iostream>
#include "optimization/exhaustiveSearch/backtracking.h"
#include "solution/solutionArray.h"
#include "stoppingCriteria/stoppingCriteria.h"
#include "problem/nQueensProblem.h"
#include "solution/domain.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_backtraking : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_backtraking);
	CPPUNIT_TEST(backtraking);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		n = 4;
		mt_rand.seed(0);
		eNQueensProblem = std::make_shared<NQueensProblem>(n);
	}

	void backtraking(void) {
		std::unique_ptr<StoppingCriteria<SOL_NQUEENSPROBLEM, unsigned int>> stoppingCriteria =
			std::make_unique<StoppingCriteria<SOL_NQUEENSPROBLEM, unsigned int>>();
		std::unique_ptr<Statistic<SOL_NQUEENSPROBLEM>> statistic = std::make_unique<Statistic<SOL_NQUEENSPROBLEM>>();

		SOL_NQUEENSPROBLEM s(n);
		Domain<unsigned int> dom(0, n);

		Backtraking<SOL_NQUEENSPROBLEM, unsigned int, unsigned int> backtraking(
			mt_rand, 
			std::move(statistic), 
			std::move(stoppingCriteria), 
			eNQueensProblem, 
			dom);

		backtraking(s);
	}

  private:
	std::mt19937 mt_rand;
	std::shared_ptr<NQueensProblem> eNQueensProblem;
	unsigned int n;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_backtraking);

#endif