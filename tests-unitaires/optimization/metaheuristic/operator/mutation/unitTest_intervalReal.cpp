///
/// @file unitTest_neighborhood.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../../../../unitTest.h"

#ifndef UNITTEST_INTERVALREAL_H
#define UNITTEST_INTERVALREAL_H

#include <memory> // std::shared_ptr std::unique_ptr

#include "optimization/metaheuristic/operator/atomicOperation.h"
#include "optimization/metaheuristic/operator/mutation/intervalReal.h"
#include "problem/oneMax.h"
#include "problem/problem.h"
#include "solution/solution.h"
#include "solutionSelection/maximization.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_intervalReal : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_intervalReal);
	CPPUNIT_TEST(operator());
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		mt_rand.seed(0);
	}

	void operator()(void) {
		unsigned int n = 20;
		Solution<double, double> s1(n);
		Solution<double, double> s2(s1);
		IntervalReal<Solution<double, double>, double, double> intervalReal(mt_rand, 20, -10, 10);
		intervalReal(s1);
		CPPUNIT_ASSERT(!(s1 == s2));
		for(unsigned int i = 0; i < n; i++) {
			CPPUNIT_ASSERT(s1(i) >= -10);
			CPPUNIT_ASSERT(s1(i) <= 10);
		}
	}

  private:
	std::mt19937 mt_rand;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_intervalReal);

#endif