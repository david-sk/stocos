///
/// @file unitTest_intervalInteger.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2020-10
/// @brief
///

#ifndef UNITTEST_INTERVALINTEGER_H
#define UNITTEST_INTERVALINTEGER_H

#include <random>
#include <memory> // std::shared_ptr std::unique_ptr

#include "optimization/metaheuristic/operator/atomicOperation.h"
#include "optimization/metaheuristic/operator/mutation/intervalInteger.h"
#include "solution/solutionArray.h"

using namespace CppUnit;

class UnitTest_intervalInteger : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_intervalInteger);
	CPPUNIT_TEST(operator());
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		mt_rand.seed(0);
	}
	void tearDown(void) {
	}

	void operator()(void) {
		unsigned int n = 20;
		SolutionArray<unsigned int, unsigned int> s1(n);
		// IntervalInteger<SolutionArray<unsigned int, unsigned int>, unsigned int, unsigned int>> intervalInteger(mt_rand, 20, 0, 10);


	}

  private:
	std::mt19937 mt_rand;
		
};

#endif