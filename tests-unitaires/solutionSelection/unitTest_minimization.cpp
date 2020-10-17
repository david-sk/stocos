///
/// @file unitTest_maximization.cpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2020-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_MINIMIZATION_H
#define UNITTEST_MINIMIZATION_H

#include "solutionSelection/minimization.h"
#include "problem/oneMax.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_minimization : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_minimization);
    CPPUNIT_TEST(minimizationSolution);
	CPPUNIT_TEST_SUITE_END();

  public:
    void minimizationSolution(void) {
        SOL_ONEMAX s1(10);
        SOL_ONEMAX s2(10);
        s1.setFitness(5);
        s2.setFitness(10);
        Minimization<SOL_ONEMAX> min;
        CPPUNIT_ASSERT(min(s1, s2));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_minimization);

#endif
