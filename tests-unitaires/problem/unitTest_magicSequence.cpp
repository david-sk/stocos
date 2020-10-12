///
/// @file unitTest_magicSequence.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_MAGICSEQUENCE_H
#define UNITTEST_MAGICSEQUENCE_H

#include "problem/problem.cpp"
#include "solution/solution.cpp"
#include "solution/solutionArray.cpp"
#include "solutionSelection/maximization.cpp"
#include "problem/magicSequence.cpp"

using namespace CppUnit;
using namespace stocos;

class UnitTest_magicSequence : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_magicSequence);
	CPPUNIT_TEST(test_loadInstance);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
	}
	void tearDown(void) {
	}

	void test_loadInstance(void) {
	}

  private:
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_magicSequence);

#endif