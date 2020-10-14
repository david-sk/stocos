///
/// @file unitTest_swap.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../../../unitTest.h"

#ifndef UNITTEST_SHUFFLE_H
#define UNITTEST_SHUFFLE_H

#include <memory> // std::shared_ptr std::unique_ptr

#include "optimization/metaheuristic/operator/shuffle.h"
#include "problem/oneMax.h"
#include "problem/problem.h"
#include "solution/solution.h"
#include "solution/solutionArray.h"
#include "solutionSelection/maximization.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_shuffle : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_shuffle);
	CPPUNIT_TEST(operator());
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		mt_rand.seed(0);
	}

	void operator()(void) {
		unsigned int N = 50;
		SOL_ONEMAX s1(1, N);
		for(unsigned int i = 0; i < N; i++) { s1(i, static_cast<int>(i % 2)); }
		SOL_ONEMAX s2(s1);

		Shuffle<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> s(mt_rand);
		s(s2);

		CPPUNIT_ASSERT(!(s1 == s2));
	}

  private:
	std::mt19937 mt_rand;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_shuffle);

#endif