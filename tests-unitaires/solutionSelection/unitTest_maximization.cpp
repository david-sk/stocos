///
/// @file unitTest_maximization.cpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2020-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_MAXIMIZATION_H
#define UNITTEST_MAXIMIZATION_H

#include "problem/oneMax.h"
#include "solutionSelection/maximization.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_maximization : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_maximization);
	CPPUNIT_TEST(maximizationSolution);
	CPPUNIT_TEST_SUITE_END();

  public:
	void maximizationSolution(void) {
		SOL_ONEMAX s1(10);
		SOL_ONEMAX s2(10);
		s1.setFitness(5);
		s2.setFitness(10);
		Maximization<SOL_ONEMAX> max;
		CPPUNIT_ASSERT(max(s2, s1));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_maximization);

#endif
