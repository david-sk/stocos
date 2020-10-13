///
/// @file unitTest_intervalInteger.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2020-10
/// @brief
///

#include "../../../../unitTest.h"

#ifndef UNITTEST_INTERVALINTEGER_H
#define UNITTEST_INTERVALINTEGER_H

#include <memory> // std::shared_ptr std::unique_ptr
#include <random>

#include "optimization/metaheuristic/operator/atomicOperation.h"
#include "optimization/metaheuristic/operator/mutation/intervalInteger.h"
#include "solution/solutionArray.h"
#include "solution/solution.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_intervalInteger : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_intervalInteger);
	CPPUNIT_TEST(operator());
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		mt_rand.seed(0);
	}

	void operator()(void) {
		unsigned int n = 20;
		SolutionArray<int, int> s1(n);
		SolutionArray<int, int> s2(s1);
		IntervalInteger<SolutionArray<int, int>, int, int> intervalInteger(mt_rand, 20, -10, 10);
		intervalInteger(s1);
		CPPUNIT_ASSERT(!(s1 == s2));
		for(unsigned int i = 0; i < n; i++) {
			CPPUNIT_ASSERT(s1(i) >= -10);
			CPPUNIT_ASSERT(s1(i) <= 10);
		}
	}

  private:
	std::mt19937 mt_rand;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_intervalInteger);

#endif
