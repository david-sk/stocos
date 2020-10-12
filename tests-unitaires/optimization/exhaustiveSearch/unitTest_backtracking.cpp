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

using namespace CppUnit;

#include "optimization/exhaustiveSearch/backtracking.cpp"
#include "problem/oneMax.cpp"
#include "problem/problem.cpp"
#include "solution/solution.cpp"
#include "solution/solutionArray.cpp"
#include "solutionSelection/maximization.cpp"
#include "stoppingCriteria/stoppingCriteria.cpp"

using namespace stocos;

class UnitTest_backtraking : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_backtraking);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		mt_rand.seed(0);
	}

	void test(void) {
		// using TYPESOL = SolutionArray<unsigned int, bool>;
		// // CPPUNIT_ASSERT(o->operator()(s) == false);

		// std::unique_ptr<StoppingCriteria<TYPESOL, unsigned int>> stoppingCriteria =
		// 	std::make_unique<StoppingCriteria<TYPESOL, unsigned int>>();
		// std::unique_ptr<Statistic<TYPESOL>> statistic = std::make_unique<Statistic<TYPESOL>>();
		// std::shared_ptr<OneMax> oneMax = std::make_shared<OneMax>(100);
		// TYPESOL s(4);

		// Backtraking<TYPESOL, unsigned int, bool> backtraking(
		// 	mt_rand, std::move(statistic), std::move(stoppingCriteria), oneMax, 2, 4);
		// backtraking.recursive(0);
	}

  private:
	std::mt19937 mt_rand;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_backtraking);

#endif