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
#include "optimization/metaheuristic/operator/mutation/intervalReal.cpp"
#include "problem/problem.cpp"
#include "problem/oneMax.cpp"
#include "solution/solution.cpp"
#include "solution/solutionArray.cpp"
#include "solutionSelection/maximization.cpp"

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
		SolutionArray<double, double> s1(n);
		SolutionArray<double, double> s2(s1);
		IntervalReal<SolutionArray<double, double>, double, double> intervalReal(mt_rand, 20, -10,
																				 10);
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